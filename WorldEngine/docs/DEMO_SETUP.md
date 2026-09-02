# Demo Level Setup for Unreal Editor

## Step 1: Open the project
- Open `WorldEngine.uproject` in Unreal Editor 5.8

## Step 2: Create a new level
- File → New Level → Basic (or Open World)
- Save it as `DemoLevel`

## Step 3: Set the GameMode
- Window → World Settings (or click the Settings icon in the toolbar)
- Under "Game Mode" section:
  - **GameMode Override**: `NLTDemoGameMode`
- The GameMode properties will show:
  - Num Agents To Spawn: 10
  - World Size: 5000
  - Random Seed: 12345
  - Auto Start Simulation: true
  - Spawn Radius: 2000

## Step 4: Press Play
- Click the green **Play** button
- You should see:
  - Output Log shows: "Demo game mode started", "Generated demo world: X districts, Y buildings", "Spawned 10 demo agents", "Simulation started"
  - 10 cube-shaped agents appear at random positions in the viewport
  - The `ANLTAgentVisualizer` actor renders them as ISM instances

## Step 5: View the Output Log
- Window → Developer Tools → Output Log
- Filter by "LogNLTDemo" to see simulation events

## Console Commands
- `showlog` - Show the output log
- `stat fps` - Show frame rate
- `stat unit` - Show game/render thread times

## What happens when you press Play:
1. `ANLTDemoGameMode::StartPlay()` is called
2. `SpawnAgentVisualizer()` - Spawns an actor with `UInstancedStaticMeshComponent`
3. `GenerateDemoWorld()` - Creates districts, buildings, roads via `UNLTWorldGeneratorSubsystem`
4. `SpawnDemoAgents()` - Creates 10 Mass entities with identity, location, intent, cognitive, needs, behavior fragments
5. `StartSimulation()` - Starts the simulation clock
6. Each frame: `ANLTAgentVisualizer::Tick()` queries Mass entities and updates ISM instances
