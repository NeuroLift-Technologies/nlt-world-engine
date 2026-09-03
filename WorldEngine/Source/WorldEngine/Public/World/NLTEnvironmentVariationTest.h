// NLTEnvironmentVariationTest.h - test for seeded micro-variation system
#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Core/NLTSimulationState.h"
#include "World/NLTEnvironmentVariation.h"

/**
 * Test harness for seeded micro-variation system.
 * Verifies that same scenario ID + different run seeds produce
 * different environmental states deterministically.
 */
namespace NLTEnvironmentVariationTest
{
    /**
     * Run a complete test of the seeded variation system.
     * Returns true if all assertions pass.
     */
    inline bool RunVariationTest()
    {
        UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("=== NLT Environment Variation Test ==="));

        // Test 1: Same scenario ID + same seed = same environment state
        {
            const FName ScenarioId(TEXT("workplace_deadline"));
            const int32 Seed1 = 12345;
            const int32 Seed2 = 12345;

            const uint32 Hash1 = UNLTEnvironmentVariationSubsystem::HashScenarioRun(ScenarioId, Seed1);
            const uint32 Hash2 = UNLTEnvironmentVariationSubsystem::HashScenarioRun(ScenarioId, Seed2);

            if (Hash1 != Hash2)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Same seed produced different hashes"));
                return false;
            }
            UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("PASS: Same seed produces same hash (0x%08x)"), Hash1);
        }

        // Test 2: Same scenario ID + different seeds = different environment states
        {
            const FName ScenarioId(TEXT("workplace_deadline"));
            const int32 Seed1 = 12345;
            const int32 Seed2 = 54321;

            const uint32 Hash1 = UNLTEnvironmentVariationSubsystem::HashScenarioRun(ScenarioId, Seed1);
            const uint32 Hash2 = UNLTEnvironmentVariationSubsystem::HashScenarioRun(ScenarioId, Seed2);

            if (Hash1 == Hash2)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Different seeds produced same hash"));
                return false;
            }
            UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("PASS: Different seeds produce different hashes (0x%08x vs 0x%08x)"), Hash1, Hash2);
        }

        // Test 3: Different scenario IDs produce different environments with same seed
        {
            const FName ScenarioId1(TEXT("workplace_deadline"));
            const FName ScenarioId2(TEXT("social_networking"));
            const int32 Seed = 12345;

            const uint32 Hash1 = UNLTEnvironmentVariationSubsystem::HashScenarioRun(ScenarioId1, Seed);
            const uint32 Hash2 = UNLTEnvironmentVariationSubsystem::HashScenarioRun(ScenarioId2, Seed);

            if (Hash1 == Hash2)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Different scenarios produced same hash"));
                return false;
            }
            UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("PASS: Different scenarios produce different hashes"));
        }

        // Test 4: Verify variation count
        {
            const int32 VariationCount = UNLTEnvironmentVariationSubsystem::GetVariationCount();
            if (VariationCount != 8)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Expected 8 variations, got %d"), VariationCount);
                return false;
            }
            UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("PASS: Variation count is %d"), VariationCount);
        }

        // Test 5: Verify FNLTEnvironmentState defaults
        {
            FNLTEnvironmentState State;
            if (State.ClutterDensity != 5)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Default clutter density not 5"));
                return false;
            }
            if (State.LightingIntensity != 1.0f)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Default lighting intensity not 1.0"));
                return false;
            }
            if (State.VfxSeed != 0)
            {
                UE_LOG(LogNLTEnvironmentVariation, Error, TEXT("FAIL: Default VFX seed not 0"));
                return false;
            }
            UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("PASS: Default environment state values correct"));
        }

        UE_LOG(LogNLTEnvironmentVariation, Log, TEXT("=== All Tests Passed ==="));
        return true;
    }
}
