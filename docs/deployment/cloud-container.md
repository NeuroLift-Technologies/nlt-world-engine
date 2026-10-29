# Cloud container deployment

**Runtime:** Godot 4.7.2 .NET / C#  
**Image:** `<DOCKER_USER>/nlt-world-engine:<tag>`  
**Build workflow:** `.github/workflows/build.yml`

## What this image does

The image imports and builds the authoritative `world-engine-godot/` project, smoke-tests startup in headless mode, and runs the Godot main scene as a long-lived process. It fetches the `asfdk-csharp` dependency at a pinned commit because the Godot project references that repository by a sibling-relative path in the local development layout.

The image is built for Linux x86_64 and targets the project's pinned Godot 4.7.2 .NET and .NET 8 toolchain.

## GitHub Actions configuration

Repository configuration expected by the workflow:

- Variable `DOCKER_USER`: Docker Hub namespace / username.
- Secret `DOCKER_PAT`: Docker Hub access token with permission to push images.
- Docker Build Cloud builder `jdub1216/neurolift-technologies`: must exist and be accessible to the Docker account used by the workflow.

A push to `main` publishes `latest` and the commit-SHA tag. Pull requests build the image without publishing it.

## Current boundary and next milestone

This container runs Godot headlessly. It does **not** yet provide the Vercel viewer with a live observer endpoint. The viewer must not treat an authored fixture or a recorded observer trace as live state. Before connecting it to this container, implement an authenticated observer transport (snapshot plus WebSocket/event stream) backed by Godot-owned physical state and events. Do not populate semantic fields from physical traces; AI-Fusion remains authoritative for semantics.
