# NLT World Engine cloud runtime
# Godot 4.7.2 .NET is pinned to match world-engine-godot/project.godot.
# The build image contains the editor; the runtime image contains only the
# dedicated-server export, its .NET assemblies, and the HTTP supervisor.
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

# Editor binary is a build-time tool only. The final image never receives it.
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

# Install the matching .NET export templates (not the Standard templates).
RUN set -eux; \
    curl -fsSL "https://downloads.godotengine.org/?version=${GODOT_VERSION}&flavor=stable&platform=templates&slug=mono_export_templates.tpz" -o /tmp/godot-templates.tpz; \
    mkdir -p /tmp/godot-templates /root/.local/share/godot/export_templates/${GODOT_VERSION}.stable.mono; \
    unzip -q /tmp/godot-templates.tpz -d /tmp/godot-templates; \
    cp -a /tmp/godot-templates/templates/. /root/.local/share/godot/export_templates/${GODOT_VERSION}.stable.mono/; \
    test -s /root/.local/share/godot/export_templates/${GODOT_VERSION}.stable.mono/linux_release.x86_64; \
    rm -rf /tmp/godot-templates /tmp/godot-templates.tpz

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

# Produce a server-only project copy. Keep the desktop project unchanged.
# Fennara capture, XR vendor bindings, and the editor/runtime MCP bridge are
# development integrations, not part of the authoritative simulation server.
RUN sed -i '/^_fennara_game_capture=/d' project.godot \
    && sed -i '/^MCPRuntimeServer=/d' project.godot \
    && sed -i 's/, "res:\/\/addons\/godot_mcp_toolkit\/plugin.cfg"//' project.godot \
    && rm -rf addons/fennara addons/godotopenxrvendors addons/godot_mcp_toolkit

# Import resources, compile the managed project, and export a Linux dedicated
# server. Godot's dedicated_server export feature strips visual resource payloads
# and forces headless mode; collision/physics resources and simulation scripts stay.
RUN godot --headless --editor --path . --audio-driver Dummy --quit \
    && dotnet build world-engine-godot.csproj --configuration Release \
    && mkdir -p /opt/server \
    && godot --headless --path . --audio-driver Dummy \
       --export-release "Linux Dedicated Server" /opt/server/nlt-world-engine.x86_64 \
    && test -x /opt/server/nlt-world-engine.x86_64 \
    && ldd /opt/server/nlt-world-engine.x86_64 \
    && ! ldd /opt/server/nlt-world-engine.x86_64 | grep -q "not found" \
    && timeout 30s /opt/server/nlt-world-engine.x86_64 --headless --audio-driver Dummy --quit-after 5

# HTTP front (/health, /run) supervises the exported server executable.
RUN dotnet publish /src/nlt-world-engine/container-host/NltContainerHost.csproj \
    --configuration Release --output /opt/host

# Runtime contains no editor, project source tree, import cache, or export SDK.
FROM mcr.microsoft.com/dotnet/aspnet:8.0-bookworm-slim AS runtime

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    libfontconfig1 libgl1 libvulkan1 \
    libx11-6 libxcursor1 libxext6 libxfixes3 libxi6 libxinerama1 \
    libxkbcommon0 libxrandr2 libxrender1 libwayland-client0 \
    libwayland-cursor0 libwayland-egl1 libdecor-0-0 libdbus-1-3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /opt/server/ /app/engine/
COPY --from=build /opt/host/ /app/host/

ENV GODOT_SILENCE_ROOT_WARNING=1
ENV DOTNET_EnableDiagnostics=0
ENV NLT_AGENT_LOOP_ENABLED=0
ENV NLT_GODOT_BIN=/app/engine/nlt-world-engine.x86_64

# Long-running HTTP service for container hosts such as Vercel Container Runtime.
# /run requires NLT_RUN_TOKEN (Bearer auth) and is disabled without it. The Fusion
# perception endpoint stays loopback-only and is not exposed here.
ENV PORT=80
EXPOSE 80
CMD ["dotnet", "/app/host/NltContainerHost.dll"]
