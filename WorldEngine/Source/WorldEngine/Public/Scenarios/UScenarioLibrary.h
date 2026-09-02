#pragma once

#include "CoreMinimal.h"
#include "Scenarios/UScenarioDataAsset.h"
#include "UScenarioLibrary.generated.h"

/**
 * Static library for discovering and loading UScenarioDataAsset instances from disk.
 * Provides Blueprint-callable access to the scenario catalog without requiring
 * manual asset references in Blueprints or C++.
 */
UCLASS()
class WORLDENGINE_API UScenarioLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Returns all UScenarioDataAsset assets found on disk. */
    UFUNCTION(BlueprintCallable, Category = "NLT|Scenario")
    static TArray<UScenarioDataAsset*> GetAllScenarios();

    /** Finds a scenario by its unique ScenarioId, or nullptr if not found. */
    UFUNCTION(BlueprintCallable, Category = "NLT|Scenario")
    static UScenarioDataAsset* GetScenarioById(FName Id);

    /** Returns all scenarios matching the given category. */
    UFUNCTION(BlueprintCallable, Category = "NLT|Scenario")
    static TArray<UScenarioDataAsset*> GetScenariosByCategory(EScenarioCategory Cat);

    /** Forces a synchronous scan of the asset registry for all scenario assets. */
    UFUNCTION(BlueprintCallable, Category = "NLT|Scenario")
    static void LoadAllScenariosFromDisk();
};