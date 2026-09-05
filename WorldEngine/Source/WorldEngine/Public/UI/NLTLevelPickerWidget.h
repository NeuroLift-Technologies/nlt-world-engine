// NLTLevelPickerWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NLTLevelPickerWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelSelected, FName, LevelId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickerClosed);

/**
 * Level picker widget shown when the player interacts with a door.
 * Displays a list of available levels as buttons.
 * Blueprint-extensible for styling and layout.
 */
UCLASS()
class WORLDENGINE_API UNLTLevelPickerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Called when a level button is clicked. */
	UPROPERTY(BlueprintAssignable, Category = "NLT|LevelPicker")
	FOnLevelSelected OnLevelSelected;

	/** Called when the picker is closed (cancel). */
	UPROPERTY(BlueprintAssignable, Category = "NLT|LevelPicker")
	FOnPickerClosed OnPickerClosed;

	/**
	 * Add a level entry to the picker.
	 * Call this for each available level before showing the widget.
	 * BlueprintCallable so Blueprint subclasses can also populate.
	 */
	UFUNCTION(BlueprintCallable, Category = "NLT|LevelPicker")
	void AddLevelEntry(const FName& LevelId, const FText& DisplayName);

	/** Clear all level entries. */
	UFUNCTION(BlueprintCallable, Category = "NLT|LevelPicker")
	void ClearEntries();

	/** Show the widget and enable input. */
	UFUNCTION(BlueprintCallable, Category = "NLT|LevelPicker")
	void ShowPicker();

	/** Hide the widget and disable input. */
	UFUNCTION(BlueprintCallable, Category = "NLT|LevelPicker")
	void HidePicker();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/** Internal structure for a level entry. */
	struct FLevelEntry
	{
		FName LevelId;
		FText DisplayName;
	};

	TArray<FLevelEntry> Entries;

	/** Blueprint-implementable event to refresh the UI after entries change. */
	UFUNCTION(BlueprintImplementableEvent, Category = "NLT|LevelPicker")
	void OnEntriesUpdated();
};
