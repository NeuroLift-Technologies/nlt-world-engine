# NLTGovernanceSubsystem

## Overview

The NLTGovernanceSubsystem integrates ASFDK-C++ (the NeuroLift Technologies Solidarity Framework port to C++) with Unreal Engine 5. It provides governance-aware AI decision-making, emotional continuity, and crisis intervention for NLT agent simulations.

## Features

- **World-level governance management** via `UNLTGovernanceSubsystem` (UWorldSubsystem)
- **Per-agent governance state** with automatic ASFDK-C++ lifecycle management
- **Interaction processing** through TOI/OTOI/RRT/Sleepwalker pillars
- **Emotional continuity** via Sleepwalker Protocol
- **Crisis intervention** via RRT Advocate
- **Blueprint-accessible API** for UE integration

## Plugin Structure

```
NLTGovernanceSubsystem/
├── NLTGovernanceSubsystem.uplugin    # Plugin descriptor
└── Source/
    └── NLTGovernanceSubsystem/
        ├── NLTGovernanceSubsystem.Build.cs
        ├── Public/
        │   ├── NLTGovernanceSubsystem.h      # Module + Subsystem API
        │   └── NLTGovernanceSubsystem.cpp    # Module implementation
        ├── Private/
        │   ├── NLTGovernanceSubsystem.cpp    # Subsystem implementation
        │   ├── AgentGovernanceState.h        # Per-agent wrapper
        │   └── AgentGovernanceState.cpp      # Per-agent implementation
        └── ThirdParty/
            └── ASFDK/                         # ASFDK-C++ headers + libs
                ├── include/
                │   ├── asfdk/
                │   ├── spdlog/
                │   ├── nlohmann/
                │   └── tl/
                └── lib/
                    └── libasfdk.a
```

## Integration Points

| UE System | Governance Boundary |
|-----------|---------------------|
| `UWorld` | Governance subsystem manager |
| `AActor` | Agent identity, governance context |
| `UMassEntity` | Fragment-based governance |
| `UAIController` | Decision governance |

## Usage

### Blueprint

1. Enable the plugin in your project
2. Access via "NLT Governance" category in Blueprint nodes
3. Call `InitializeAgent` when spawning agents
4. Call `ProcessInteraction` to process agent interactions

### C++

```cpp
// Get the governance subsystem
auto* GovSys = UNLTGovernanceSubsystem::Get(GetWorld());

// Initialize an agent
GovSys->InitializeAgent("Agent_1", "Test Agent");

// Process an interaction
FString Result = GovSys->ProcessInteraction("Agent_1", "Hello, how are you?", "user_input");

// Assess the agent
FString Assessment = GovSys->AssessAgent("Agent_1", "I'm feeling stressed");
```

## Dependencies

- ASFDK-C++ (included as ThirdParty)
- Unreal Engine 5.3+
- MassEntity module
- Json/JsonUtilities modules

## Build Requirements

The plugin requires the ASFDK-C++ static library (`libasfdk.a`) to be built and placed in `Source/NLTGovernanceSubsystem/ThirdParty/ASFDK/lib/`.

Build command for the static library:
```bash
cd asfdk-cplus
g++ -std=c++23 -O2 -c packages/asfdk/src/ASFDK.cpp packages/toi/src/TermsOfInteraction.cpp packages/otoi/src/OTOIManager.cpp packages/rrt-advocate/src/*.cpp packages/sleepwalker/src/*.cpp -I packages/asfdk/include -I packages/toi/include -I packages/otoi/include -I packages/rrt-advocate/include -I packages/sleepwalker/include -I packages/include
ar rcs libasfdk.a *.o
```

## License

Internal use only — NeuroLift Technologies organization.
