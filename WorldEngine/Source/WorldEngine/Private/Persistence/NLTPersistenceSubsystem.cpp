#include "Persistence/NLTPersistenceSubsystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTPersistence);

void UNLTPersistenceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogNLTPersistence, Log, TEXT("Persistence subsystem initialized"));
}

void UNLTPersistenceSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

bool UNLTPersistenceSubsystem::SaveGame(const FString& SlotName)
{
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField(TEXT("SlotName"), SlotName);
    JsonObject->SetNumberField(TEXT("SimulationTick"), 0);
    JsonObject->SetNumberField(TEXT("WorldTime"), 0.0);
    JsonObject->SetNumberField(TEXT("TimeOfDay"), 12.0);
    JsonObject->SetNumberField(TEXT("RandomSeed"), 12345);

    FString JsonString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    FString FilePath = GetSaveFilePath(SlotName);
    bool bSuccess = FFileHelper::SaveStringToFile(JsonString, *FilePath);
    UE_LOG(LogNLTPersistence, Log, TEXT("Save game %s: %s"), *SlotName, bSuccess ? TEXT("SUCCESS") : TEXT("FAILED"));
    return bSuccess;
}

bool UNLTPersistenceSubsystem::LoadGame(const FString& SlotName)
{
    FString FilePath = GetSaveFilePath(SlotName);
    if (!FPaths::FileExists(FilePath))
    {
        UE_LOG(LogNLTPersistence, Warning, TEXT("Save game %s not found"), *SlotName);
        return false;
    }

    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        UE_LOG(LogNLTPersistence, Warning, TEXT("Failed to load save game %s"), *SlotName);
        return false;
    }

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    if (!FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        UE_LOG(LogNLTPersistence, Warning, TEXT("Failed to parse save game %s"), *SlotName);
        return false;
    }

    UE_LOG(LogNLTPersistence, Log, TEXT("Loaded save game: %s"), *SlotName);
    return true;
}

bool UNLTPersistenceSubsystem::DoesSaveGameExist(const FString& SlotName) const
{
    return FPaths::FileExists(GetSaveFilePath(SlotName));
}

bool UNLTPersistenceSubsystem::DeleteSaveGame(const FString& SlotName)
{
    FString FilePath = GetSaveFilePath(SlotName);
    if (FPaths::FileExists(FilePath))
    {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        bool bSuccess = PlatformFile.DeleteFile(*FilePath);
        UE_LOG(LogNLTPersistence, Log, TEXT("Delete save game %s: %s"), *SlotName, bSuccess ? TEXT("SUCCESS") : TEXT("FAILED"));
        return bSuccess;
    }
    return false;
}

TArray<FString> UNLTPersistenceSubsystem::GetAllSaveSlots() const
{
    TArray<FString> SaveSlots;
    FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames");
    IFileManager::Get().FindFiles(SaveSlots, *SaveDir, TEXT(".json"));
    return SaveSlots;
}

FString UNLTPersistenceSubsystem::GetSaveFilePath(const FString& SlotName) const
{
    return FPaths::ProjectSavedDir() / TEXT("SaveGames") / (SlotName + TEXT(".json"));
}
