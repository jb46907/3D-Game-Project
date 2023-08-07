// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameProjectWinWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UGameProjectWinWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnNextLevelButtonClicked(FName NextLevelName);

	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();
};
