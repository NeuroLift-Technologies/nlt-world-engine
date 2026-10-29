# NLT World Engine cloud runtime
# Godot 4.7.2 .NET is pinned to match world-engine-godot/project.godot.
FROM mcr.microsoft.com/dotnet/sdk:8.0-bookworm-slim AS build

ARG GODOT_VERSION=4.7.2
ARG ASFDK_CSHARP_COMMIT=eb2887d7076bb61ca916d8fad778bb6213290421

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates curl git unzip \
    libasound2 libfontconfig1 libgl1 libpulse0 libvulkan1 \
    libx11-6 libxcursor1 libxext6 libxfixes3 libxi6 libxinerama1 \
    libxkbcommon0 libxrandr2 libxrender1 libwayland-client0 \
    libwayland-cursor0 libwayland-egl1 libdecor-0-0 libdbus-1-3 \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /opt/godot \
    && curl -fsSL "https://downloads.godotengine.org/?version=${GODOT_VERSION}&flavor=stable&platform=linux.64&slug=mono_linux_x86_64.zip" -o /tmp/godot.zip \
    && unzip -q /tmp/godot.zip -d /opt/godot \
    && rm /tmp/godot.zip \
    && GODOT_BIN="$(find /opt/godot -maxdepth 1 -type f -executable -name 'Godot*' | head -n 1)" \
    && test -n "$GODOT_BIN" \
    && ln -s "$GODOT_BIN" /usr/local/bin/godot \
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

# Import assets and generate GodotSharp build support before compiling the C# project.
RUN godot --headless --editor --path . --audio-driver Dummy --quit \
    && dotnet build world-engine-godot.csproj --configuration Debug \
    && godot --headless --path . --audio-driver Dummy --quit-after 5

# Keep the initial runtime simple and reproducible. A later optimization can
# replace the editor binary with a dedicated-server export template.
FROM mcr.microsoft.com/dotnet/aspnet:8.0-bookworm-slim AS runtime

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    libasound2 libfontconfig1 libgl1 libpulse0 libvulkan1 \
    libx11-6 libxcursor1 libxext6 libxfixes3 libxi6 libxinerama1 \
    libxkbcommon0 libxrandr2 libxrender1 libwayland-client0 \
    libwayland-cursor0 libwayland-egl1 libdecor-0-0 libdbus-1-3 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /opt/godot /opt/godot
RUN GODOT_BIN="$(find /opt/godot -maxdepth 1 -type f -executable -name 'Godot*' | head -n 1)" \
    && test -n "$GODOT_BIN" \
    && ln -s "$GODOT_BIN" /usr/local/bin/godot

WORKDIR /app
COPY --from=build /src/nlt-world-engine/world-engine-godot /app/world-engine-godot

ENV GODOT_SILENCE_ROOT_WARNING=1
ENV DOTNET_EnableDiagnostics=0
ENV NLT_AGENT_LOOP_ENABLED=0

# Headless runtime: Godot remains authoritative for physical simulation.
# This image does not yet expose the viewer's live observer API; that transport
# must be implemented and wired to engine-owned state before the viewer can connect.
CMD ["godot", "--headless", "--path", "/app/world-engine-godot", "--audio-driver", "Dummy"]
