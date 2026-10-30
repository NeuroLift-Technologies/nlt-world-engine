# NLT World Engine cloud runtime
# Godot 4.7.2 .NET is pinned to match world-engine-godot/project.godot.
FROM mcr.microsoft.com/dotnet/sdk:8.0-bookworm-slim AS build

ARG GODOT_VERSION=4.7.2
ARG ASFDK_CSHARP_COMMIT=eb2887d7076bb61ca916d8fad778bb6213290421

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates curl git unzip \
    libfontconfig1 libgl1 libvulkan1 \
    libx11-6 libxcursor1 libxext6 libxfixes3 libxi6 libxinerama1 \
    libxkbcommon0 libxrandr2 libxrender1 libwayland-client0 \
    libwayland-cursor0 libwayland-egl1 libdecor-0-0 libdbus-1-3 \
    && rm -rf /var/lib/apt/lists/*

RUN set -eux; mkdir -p /opt/godot \
    && curl -fsSL "https://downloads.godotengine.org/?version=${GODOT_VERSION}&flavor=stable&platform=linux.64&slug=mono_linux_x86_64.zip" -o /tmp/godot.zip \
    && unzip -q /tmp/godot.zip -d /opt/godot \
    && rm /tmp/godot.zip \
    && GODOT_BIN="$(find /opt/godot -type f -name 'Godot_v*.x86_64' | head -n 1)" \
    && test -n "$GODOT_BIN" \
    && chmod +x "$GODOT_BIN" \
    && ln -s "$GODOT_BIN" /usr/local/bin/godot \
    && ldd "$GODOT_BIN" \
    && godot --version

WORKDIR /src/nlt-world-engine
COPY . .

# The Godot project references ASFDK-C# as a sibling repository. Fetch a pinned
# commit so the container build has the same dependency path without relying on
# a developer's local nlt-repos directory.
RUN git init /src/asfdk-csharp \
    && git -C /src/asfdk-csharp remote add origin https://github.com/NeuroLift-Technologies/asfdk-csharp.git \
    && git -C /src/asfdk-csharp fetch --depth 1 origin "${ASFDK_CSHARP_COMMIT}" \
    && git -C /src/asfdk-csharp checkout --detach FETCH_HEAD

WORKDIR /src/nlt-world-engine/world-engine-godot

# The headless server has no XR device and the repository does not include the
# Fennara Linux editor GDExtension binary. Keep those optional integrations out
# of this container-only project copy; the desktop project remains unchanged.
RUN sed -i '/^_fennara_game_capture=/d' project.godot \
    && rm -f addons/fennara/fennara.gdextension addons/fennara/fennara.gdextension.uid \
              addons/godotopenxrvendors/plugin.gdextension addons/godotopenxrvendors/plugin.gdextension.uid

# Import assets and generate GodotSharp build support before compiling the C# project.
RUN godot --headless --editor --path . --audio-driver Dummy --quit \
    && dotnet build world-engine-godot.csproj --configuration Debug \
    && godot --headless --path . --audio-driver Dummy --quit-after 5

# HTTP front (/health, /run) that supervises the Godot process in the runtime image.
RUN dotnet publish /src/nlt-world-engine/container-host/NltContainerHost.csproj \
    --configuration Release --output /opt/host

# Headless runtime: keep only the shared libraries required by the Linux Godot
# Mono binary. Audio backends are intentionally omitted; --audio-driver Dummy
# is used for both import/validation and the supervised server process.
FROM mcr.microsoft.com/dotnet/aspnet:8.0-bookworm-slim AS runtime

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    libfontconfig1 libgl1 libvulkan1 \
    libx11-6 libxcursor1 libxext6 libxfixes3 libxi6 libxinerama1 \
    libxkbcommon0 libxrandr2 libxrender1 libwayland-client0 \
    libwayland-cursor0 libwayland-egl1 libdecor-0-0 libdbus-1-3 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /opt/godot /opt/godot
RUN GODOT_BIN="$(find /opt/godot -type f -name 'Godot_v*.x86_64' | head -n 1)" \
    && test -n "$GODOT_BIN" \
    && chmod +x "$GODOT_BIN" \
    && ln -s "$GODOT_BIN" /usr/local/bin/godot

WORKDIR /app
COPY --from=build /src/nlt-world-engine/world-engine-godot /app/world-engine-godot
COPY --from=build /opt/host /app/host

ENV GODOT_SILENCE_ROOT_WARNING=1
ENV DOTNET_EnableDiagnostics=0
ENV NLT_AGENT_LOOP_ENABLED=0

# Long-running HTTP service for container hosts such as Vercel Container Runtime: listens on
# 0.0.0.0:$PORT (default 80), keeps headless Godot alive as a child process, serves /health and /run.
# /run needs NLT_RUN_TOKEN (Bearer auth) and is disabled without it. The Fusion perception endpoint
# stays loopback-only and is not exposed here.
ENV PORT=80
EXPOSE 80
CMD ["dotnet", "/app/host/NltContainerHost.dll"]
