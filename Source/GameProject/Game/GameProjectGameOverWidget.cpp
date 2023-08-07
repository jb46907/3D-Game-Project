// Fill out your copyright notice in the Description page of Project Settings.


#include "GameProjectGameOverWidget.h"

#include "Kismet/GameplayStatics.h"

void UGameProjectGameOverWidget::OnExitButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MenuLevel"), true);
}

void UGameProjectGameOverWidget::OnRestartButtonClicked()
{
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName), true);
}
