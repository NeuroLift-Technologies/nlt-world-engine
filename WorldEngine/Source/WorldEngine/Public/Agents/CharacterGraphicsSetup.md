# Character Graphics Enhancement System

This document provides instructions for setting up the enhanced character graphics system for the `BP_AvatarCharacter` template.

## Overview

The character graphics system has been enhanced with:

1. **PBR Material System** - Physically Based Rendering materials with advanced parameters
2. **Dynamic Material Instances** - Materials that respond to cognitive state in real-time
3. **Visual State System** - Stress, Focus, and Team-based visual feedback
4. **Particle Effects** - Stress particles, focus auras, and interaction effects
5. **Post-Processing** - Character-specific post-processing volumes
6. **Team Identification** - Color-coded materials based on team assignment

## Setup Instructions

### 1. Material System Setup

#### Base Materials Required

Create these materials in `/Game/Kits/Characters/Materials/`:

- **M_Character_Base** - Master material for all characters
- **M_Character_Head** - Head-specific material
- **M_Character_Limbs** - Limbs-specific material
- **M_Stressed** - Material for stressed state
- **M_Focused** - Material for focused state
- **M_Team_Neutral** - Neutral team material
- **M_Team_A** - Team A material
- **M_Team_B** - Team B material
- **M_Team_C** - Team C material

#### Master Material Parameters

The master material should include these parameters:

```
// Vector Parameters
- TeamColor (Vector): Team identification color
- BaseColor (Vector): Base material color
- EmissiveColor (Vector): Emissive color for effects

// Scalar Parameters
- StressLevel (Float): Current stress level (0.0 - 1.0)
- FocusLevel (Float): Current focus level (0.0 - 1.0)
- PulseIntensity (Float): Pulsing effect intensity (0.0 - 1.0)
- VisualState (Float): Current visual state (0=Normal, 1=Focused, 2=Stressed, 3=Interacting)
- WearAmount (Float): Wear/damage amount (0.0 - 1.0)
- Metallic (Float): Metallic value
- Roughness (Float): Roughness value
- NormalIntensity (Float): Normal map intensity

// Texture Parameters
- BaseColorTexture (Texture2D): Albedo/Diffuse texture
- NormalTexture (Texture2D): Normal map
- RoughnessTexture (Texture2D): Roughness map
- MetallicTexture (Texture2D): Metallic map
- EmissiveTexture (Texture2D): Emissive texture
```

#### Material Function Graph

Recommended material graph structure:

```
Base Color -> Multiply by TeamColor (Lerp based on VisualState)
            -> Add Stress Effects (Red tint when stressed)
            -> Add Focus Effects (Glow/Emissive when focused)
            -> Apply Wear/Damage
            -> Output to Emissive and BaseColor

Normal -> Multiply by NormalIntensity
      -> Output to Normal

Roughness -> Multiply by StressLevel (higher stress = rougher)
          -> Output to Roughness

Metallic -> Add MetallicTexture
         -> Output to Metallic
```

### 2. Material Instances

Create material instances for different variations:

- **MI_Character_Default** - Default character appearance
- **MI_Character_SciFi** - Science fiction robot style
- **MI_Character_Organic** - Organic/biological appearance
- **MI_Character_Metallic** - Metallic/robotic appearance

### 3. Particle Systems Setup

Create these particle systems in `/Game/Kits/Characters/Particles/`:

#### Stress Particles (P_Stress_Character)
- **Type**: GPU Sprite
- **Spawn Rate**: 10-50 particles per second
- **Lifetime**: 0.5-2.0 seconds
- **Color**: Red to Orange gradient
- **Size**: Small (2-10 units)
- **Velocity**: Upward from character
- **Material**: M_Particle_Stress (heat distortion effect)
- **Parameters**: SpawnRateScale (Float), Intensity (Float)

#### Focus Aura Particles (P_Focus_Aura)
- **Type**: GPU Beam or Ribbon
- **Spawn Rate**: 1-5 particles per second
- **Lifetime**: 1.0-3.0 seconds
- **Color**: Blue to White gradient
- **Size**: Medium (10-30 units)
- **Behavior**: Orbit around character
- **Material**: M_Particle_Focus (glowing energy effect)
- **Parameters**: AuraIntensity (Float), Intensity (Float)

#### Interaction Particles (P_Interaction)
- **Type**: CPU Sprite
- **Spawn Rate**: 5-20 particles on interaction
- **Lifetime**: 0.3-1.0 seconds
- **Color**: Yellow to Green gradient
- **Size**: Small to Medium (5-15 units)
- **Behavior**: Burst from interaction point
- **Material**: M_Particle_Interaction (sparkle effect)

### 4. Particle System Components Setup

In `BP_AvatarCharacter` blueprint:

1. Add **ParticleSystemComponent** named "StressParticles"
   - Template: P_Stress_Character
   - Auto Activate: false
   - Relative Location: (0, 0, 100)

2. Add **ParticleSystemComponent** named "FocusAuraParticles"
   - Template: P_Focus_Aura
   - Auto Activate: false
   - Relative Location: (0, 0, 0)

3. Add **ParticleSystemComponent** named "InteractionParticles"
   - Template: P_Interaction
   - Auto Activate: false
   - Relative Location: (50, 0, 50)

### 5. Post-Processing Volume Setup

Create a post-processing material in `/Game/Kits/Characters/PostProcess/`:

- **M_PostProcess_Character** - Character-specific post-processing

Material parameters:
- StressAmount (Float): Amount of stress distortion
- FocusAmount (Float): Amount of focus sharpening/glow
- ChromaticAberration (Float): Color fringing
- BloomIntensity (Float): Bloom effect strength
- VignetteIntensity (Float): Vignette strength

In `BP_AvatarCharacter` blueprint:

1. Add **UPostProcessComponent** named "PostProcessVolume"
   - Priority: -1
   - Blend Weight: 0.0 (initially disabled)
   - Settings: Use M_PostProcess_Character

### 6. Team Color System

Team colors are defined in the code:

- **Neutral**: Gray (0.7, 0.7, 0.7)
- **Team A**: Blue (0.2, 0.6, 1.0)
- **Team B**: Orange (1.0, 0.4, 0.2)
- **Team C**: Green (0.3, 0.8, 0.3)

These can be customized in the character blueprint or in the material.

### 7. Visual State Transitions

The character automatically transitions between visual states:

- **Normal**: Stress < 0.4, Focus < 0.7
- **Focused**: Focus > 0.7 (regardless of stress)
- **Stressed**: Stress > 0.8
- **Interacting**: During interaction (requires implementation)

State affects:
- Material parameters (color, emissive, etc.)
- Particle system activation
- Post-processing intensity

### 8. Dynamic Material Parameters

The system automatically updates these material parameters every frame:

- TeamColor: Based on team assignment
- StressLevel: Current cognitive stress (0.0 - 1.0)
- FocusLevel: Current cognitive focus (0.0 - 1.0)
- PulseIntensity: Time-based pulsing effect (0.0 - 1.0)
- VisualState: Current visual state as float

## Blueprints Configuration

### BP_AvatarCharacter Setup

1. **Mesh**: Use Skeletel Mesh Component
   - Skeletal Mesh: SK_SimBody or custom character mesh
   - Materials: Assign created materials to each slot

2. **Materials**:
   - Element 0 (Body): M_Character_Base or material instance
   - Element 1 (Head): M_Character_Head or material instance
   - Element 2 (Limbs): M_Character_Limbs or material instance

3. **Particles**:
   - StressParticles: Assign P_Stress_Character
   - FocusAuraParticles: Assign P_Focus_Aura
   - InteractionParticles: Assign P_Interaction

4. **Cognitive State**:
   - CognitiveState component is automatically created
   - Thresholds can be adjusted in the character properties

5. **Team Assignment**:
   - Set Team property to assign team color
   - Team A, B, C, or Neutral

## C++ Class Integration

The `AAvatarCharacter` class now includes:

### Components
- `USkeletalMeshComponent` (inherited from ACharacter)
- `UParticleSystemComponent` x3 (Stress, Focus, Interaction)
### Components
- `USkeletalMeshComponent` (inherited from ACharacter)
- `UParticleSystemComponent` x3 (Stress, Focus, Interaction)
- `UPostProcessComponent`
- `ULTCognitiveStateComponent`
- `UNLTAvatarVisualComponent` (cognitive-state-driven status ring, emissive glow, state particles)
- `UPostProcessComponent`
- `ULTCognitiveStateComponent`

### Properties
- Team: ECharacterTeam (Neutral, TeamA, TeamB, TeamC)
- BodyMaterial, HeadMaterial, LimbsMaterial: UMaterialInterface*
- StressParticles, FocusAuraParticles, InteractionParticles: UParticleSystem*
- StressThresholdForParticles: float (default 0.6)
- FocusThresholdForAura: float (default 0.7)

### Functions
- UpdateVisualState(): Determines current visual state
- UpdateMaterials(): Updates all material parameters
- UpdateParticleEffects(): Activates/deactivates particles
- UpdatePostProcessing(): Updates post-processing effects
- GetTeamColor(): Returns color based on team
- GetStressLevel(): Returns current stress from cognitive state
- GetFocusLevel(): Returns current focus from cognitive state

## Mass Agent Visualizer

The `ANLTAgentVisualizer` has been enhanced with similar capabilities for mass entity visualization:

### Features
- Hierarchical Instanced Static Mesh (HISM) for better performance
- Team color support for individual agents
- Stress and focus-based coloring
- Particle effects for groups of stressed/focused agents
- Global post-processing based on overall state

### Configuration
- AgentMesh: UStaticMesh* (default: SM_SimBody_Base)
- AgentMaterial: UMaterialInterface* (base material)
- StressedMaterial: UMaterialInterface* (stress state material)
- FocusedMaterial: UMaterialInterface* (focus state material)
- StressParticles: UParticleSystem*
- FocusAuraParticles: UParticleSystem*

## Performance Considerations

1. **LODs**: Implement LODs for character meshes
   - LOD0: High detail (0-50m)
   - LOD1: Medium detail (50-100m)
   - LOD2: Low detail (100-200m)
   - LOD3: Billboard (200m+)

2. **Culling**: Use proper culling distances
   - Characters: 200-500m
   - Particles: 100-300m
   - Post-processing: 50-100m

3. **Material Complexity**:
   - Use Material LODs
   - Simplify materials at distance
   - Use lower quality textures at distance

4. **Particle Optimization**:
   - Use GPU particles where possible
   - Limit particle counts
   - Use distance-based quality scaling

5. **Instancing**:
   - Use HISM for crowd visualization
   - Limit instance counts per component
   - Use appropriate hierarchy levels

## Asset Creation Checklist

### Textures Required
- [ ] T_SimBody_BaseColor - 2048x2048, PBR albedo
- [ ] T_SimBody_Normal - 2048x2048, Normal map
- [ ] T_SimBody_Roughness - 2048x2048, Roughness map
- [ ] T_SimBody_Metallic - 2048x2048, Metallic map
- [ ] T_SimBody_Emissive - 2048x2048, Emissive map
- [ ] T_SimBody_AO - 2048x2048, Ambient Occlusion

### Materials Required
- [ ] M_Character_Base - Master material
- [ ] MI_Character_Default - Default instance
- [ ] MI_Character_Stressed - Stressed instance
- [ ] MI_Character_Focused - Focused instance
- [ ] M_Particle_Stress - Stress particle material
- [ ] M_Particle_Focus - Focus particle material
- [ ] M_Particle_Interaction - Interaction particle material
- [ ] M_PostProcess_Character - Post-processing material

### Particle Systems Required
- [ ] P_Stress_Character - Stress particles
- [ ] P_Focus_Aura - Focus aura particles
- [ ] P_Interaction - Interaction particles

### Meshes Required
- [ ] SK_SimBody - Character skeletal mesh
- [ ] SM_SimBody_Base - Static mesh fallback
- [ ] SK_SimBody_LOD1 - LOD1 mesh
- [ ] SK_SimBody_LOD2 - LOD2 mesh

## Implementation Notes

1. **Cognitive State Integration**: The system automatically reads stress and focus values from the `ULTCognitiveStateComponent` attached to each character.

2. **Real-time Updates**: All visual effects are updated every frame in the `Tick()` function.

3. **Blueprint Override**: All properties can be overridden in blueprints for specific character variations.

4. **Material Parameter Names**: Ensure your materials use the exact parameter names defined in the C++ code.

5. **Testing**: Test with different stress/focus values to ensure smooth transitions between visual states.

## Usage Example

```cpp
// Create a character with custom settings
AAvatarCharacter* Character = World->SpawnActor<AAvatarCharacter>(Location, Rotation);
Character->Team = ECharacterTeam::TeamA;
Character->StressThresholdForParticles = 0.5f;
Character->FocusThresholdForAura = 0.6f;
Character->BodyMaterial = CustomMaterial;
```

## Troubleshooting

### Common Issues

1. **Materials not updating**: Check that parameter names match exactly
2. **Particles not appearing**: Verify templates are assigned and thresholds are met
3. **Team colors not working**: Ensure Team property is set correctly
4. **Performance issues**: Reduce particle counts, simplify materials, or reduce draw distance

### Debugging

Enable debug visualization:
- Use `bShowDebugText = true` in NLTAgentVisualizer
- Check `LastEntityCount` for mass entity count
- Monitor material parameter values in the material editor

## Future Enhancements

1. **Character Customization**: Add support for different body types, clothing, accessories
2. **Animation System**: Add stress/focus-based animations
3. **Facial Expressions**: Add facial animations based on emotional state
4. **Clothing Damage**: Add wear/tear effects based on damage
5. **Weather Effects**: Add weather-based material changes (wet, snow, etc.)

---

This graphics system provides a comprehensive foundation for visualizing character states and creating immersive, responsive character visuals in your NeuroLift Technologies simulations.