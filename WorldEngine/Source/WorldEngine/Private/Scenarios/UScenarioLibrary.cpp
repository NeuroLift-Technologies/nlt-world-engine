#include "Scenarios/UScenarioLibrary.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "UObject/SoftObjectPath.h"
#include "AssetRegistry/IAssetRegistry.h"

TArray<UScenarioDataAsset*> UScenarioLibrary::GetAllScenarios()
{
    TArray<UScenarioDataAsset*> Results;

    if (IAssetRegistry* AssetRegistry = IAssetRegistry::Get())
    {
        AssetRegistry->WaitForCompletion();
    }

    UAssetManager& AssetManager = UAssetManager::Get();
    TArray<FAssetData> AssetDataArray;

    FARFilter Filter;
    Filter.ClassPaths.Add(UScenarioDataAsset::StaticClass()->GetClassPathName());
    Filter.bRecursiveClasses = true;

    AssetManager.GetAssetRegistry().GetAssets(Filter, AssetDataArray);

    for (const FAssetData& AssetData : AssetDataArray)
    {
        if (UScenarioDataAsset* Scenario = Cast<UScenarioDataAsset>(AssetData.GetAsset()))
        {
            Results.Add(Scenario);
        }
    }

    return Results;
}

UScenarioDataAsset* UScenarioLibrary::GetScenarioById(FName Id)
{
    TArray<UScenarioDataAsset*> AllScenarios = GetAllScenarios();
    for (UScenarioDataAsset* Scenario : AllScenarios)
    {
        if (Scenario && Scenario->ScenarioId == Id)
        {
            return Scenario;
        }
    }

    LoadAllScenariosFromDisk();

    AllScenarios = GetAllScenarios();
    for (UScenarioDataAsset* Scenario : AllScenarios)
    {
        if (Scenario && Scenario->ScenarioId == Id)
        {
            return Scenario;
        }
    }

    return nullptr;
}

TArray<UScenarioDataAsset*> UScenarioLibrary::GetScenariosByCategory(EScenarioCategory Cat)
{
    TArray<UScenarioDataAsset*> Results;
    TArray<UScenarioDataAsset*> AllScenarios = GetAllScenarios();

    for (UScenarioDataAsset* Scenario : AllScenarios)
    {
        if (Scenario && Scenario->Category == Cat)
        {
            Results.Add(Scenario);
        }
    }

    return Results;
}

void UScenarioLibrary::LoadAllScenariosFromDisk()
{
    UAssetManager& AssetManager = UAssetManager::Get();
    TArray<FAssetData> AssetDataArray;

    FARFilter Filter;
    Filter.ClassPaths.Add(UScenarioDataAsset::StaticClass()->GetClassPathName());
    Filter.bRecursiveClasses = true;

    AssetManager.GetAssetRegistry().GetAssets(Filter, AssetDataArray);

    TArray<FSoftObjectPath> PathsToLoad;
    for (const FAssetData& AssetData : AssetDataArray)
    {
        PathsToLoad.Add(FSoftObjectPath(AssetData.GetSoftObjectPath()));
    }

    if (PathsToLoad.Num() > 0)
    {
        FStreamableManager& Streamable = AssetManager.GetStreamableManager();
        Streamable.RequestSyncLoad(PathsToLoad);
    }
}