// Fill out your copyright notice in the Description page of Project Settings.


#include "GameProjectWinWidget.h"
#include "Kismet/GameplayStatics.h"

void UGameProjectWinWidget::OnNextLevelButtonClicked(FName NextLevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}

void UGameProjectWinWidget::OnExitButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MenuLevel"), true);
}
