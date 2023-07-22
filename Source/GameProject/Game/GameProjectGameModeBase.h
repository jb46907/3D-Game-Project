
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameProjectGameModeBase.generated.h"

class UGameProjectWidget;

UCLASS()
class GAMEPROJECT_API AGameProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	UGameProjectWidget* GameWidget;

	UPROPERTY()
	class AGameProjectTimer* TimerManager;

	UPROPERTY()
	class AGameProjectItemBase* ItemBase;

	UPROPERTY()
	class AGameProjectCharacter* PlayerCharacter;
	
	FVector SpawnLocation;
	
	FRotator SpawnRotation;
	
	virtual void BeginPlay() override;

	void UpdateItemText();

public:
	virtual void StopTimer();
	
	virtual void UpdateTimer();
	
	bool AreAllItemsCollected() const;
	
	void ItemCollected();
};
