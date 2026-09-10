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
├── ThirdParty/
│   └── ASFDK/                         # ASFDK-C++ (symlink to asfdk-cplus)
│       ├── packages/                  # Source + headers (via symlink)
│       └── lib/
│           └── libasfdk.a             # Pre-built static library
└── Source/
    └── NLTGovernanceSubsystem/
        ├── NLTGovernanceSubsystem.Build.cs
        ├── Public/
        │   └── NLTGovernanceSubsystem.h    # Module + Subsystem API
        ├── Private/
        │   ├── NLTGovernanceSubsystem.cpp  # Subsystem implementation
        │   ├── AgentGovernanceState.h      # Per-agent wrapper
        │   └── AgentGovernanceState.cpp    # Per-agent implementation
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
- Unreal Engine 5.8+
- MassEntity module
- Json/JsonUtilities modules

## Build Requirements

The plugin requires the ASFDK-C++ static library (`libasfdk.a`) to be built and placed in `Source/NLTGovernanceSubsystem/ThirdParty/ASFDK/lib/`.

### Prerequisites

- C++ compiler with C++20 support (g++ 12+, clang++ 15+)
- UE 5.8 defaults to C++20 (`BuildSettingsVersion.V7`); the ASFDK library must match.

### Build command for the static library

```bash
cd asfdk-cplus
g++ -std=c++20 -O2 -c \
  packages/asfdk/src/ASFDK.cpp \
  packages/toi/src/TermsOfInteraction.cpp \
  packages/toi/src/TOIManager.cpp \
  packages/otoi/src/OTOIManager.cpp \
  packages/rrt-advocate/src/BehavioralLayer.cpp \
  packages/rrt-advocate/src/BurnoutDetector.cpp \
  packages/rrt-advocate/src/CrisisAssessor.cpp \
  packages/rrt-advocate/src/CrisisDetector.cpp \
  packages/rrt-advocate/src/CrisisEngine.cpp \
  packages/rrt-advocate/src/KeywordLayer.cpp \
  packages/rrt-advocate/src/RRTAdvocate.cpp \
  packages/rrt-advocate/src/RRTTypes.cpp \
  packages/rrt-advocate/src/SentimentLayer.cpp \
  packages/sleepwalker/src/ConsentManager.cpp \
  packages/sleepwalker/src/ContinuityManager.cpp \
  packages/sleepwalker/src/SleepwalkerProtocol.cpp \
  packages/sleepwalker/src/StateDetector.cpp \
  -I packages/asfdk/include \
  -I packages/toi/include \
  -I packages/otoi/include \
  -I packages/rrt-advocate/include \
  -I packages/sleepwalker/include \
  -I packages/include
ar rcs libasfdk.a *.o
```

### Verify the build (standalone test)

```bash
g++ -std=c++20 -O2 \
  packages/asfdk/tests/standalone_test.cpp \
  libasfdk.a \
  -I packages/asfdk/include \
  -I packages/toi/include \
  -I packages/otoi/include \
  -I packages/rrt-advocate/include \
  -I packages/sleepwalker/include \
  -I packages/include \
  -o standalone_test && ./standalone_test
```

All 37 standalone tests should pass.

## License

Internal use only — NeuroLift Technologies organization.
