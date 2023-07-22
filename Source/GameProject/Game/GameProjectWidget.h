
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameProjectWidget.generated.h"

UCLASS()
class GAMEPROJECT_API UGameProjectWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void SetItemText(int32 ItemsCollected, int32 ItemsInLevel);	

	UFUNCTION(BlueprintImplementableEvent)
	void SetTimerText(int32 TimerSeconds);

	UFUNCTION(BlueprintImplementableEvent)
	void SetKeyIcon(int32 TimerSeconds);
};
