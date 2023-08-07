
#include "GameProjectGameModeBase.h"

#include "GameProjectCharacter.h"
#include "GameProjectTimer.h"
#include "GameProjectWidget.h"
#include "GameProjectGameOverWidget.h"
#include "GameProjectWinWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameProject/Items/GameProjectARotatingButton.h"
#include "GameProject/Items/GameProjectItemBase.h"
#include "Kismet/GameplayStatics.h"

void AGameProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameProjectItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();
	
	if (GameWidgetClass)
	{
		GameWidget = Cast<UGameProjectWidget>(CreateWidget(GetWorld(),GameWidgetClass));
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
	
	TimerManager = GetWorld()->SpawnActor<AGameProjectTimer>();
	if (TimerManager)
	{
		TimerManager->StartTimer();
	}

	TArray<AActor*> Buttons;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameProjectARotatingButton::StaticClass(), Buttons);

	for (AActor* button : Buttons)
	{
		AGameProjectARotatingButton* RotatingButton = Cast<AGameProjectARotatingButton>(button);
		if (RotatingButton)
		{
			RotatingButton->UpdateButtonLocation(RotatingButton->bIsBtnPressed);
		}
	}
}

void AGameProjectGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void AGameProjectGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}

void AGameProjectGameModeBase::RemainingLife()
{
	Lives--;
}

int32 AGameProjectGameModeBase::GetLives() const
{
	return Lives;
}

bool AGameProjectGameModeBase::AreAllItemsCollected() const
{
	return ItemsCollected == ItemsInLevel;
}

void AGameProjectGameModeBase::StopTimer()
{
	TimerManager->StopTimer();
}

void AGameProjectGameModeBase::UpdateTimer()
{
	GameWidget->SetTimerText(TimerManager->GetElapsedTime());
}

void AGameProjectGameModeBase::GameOver()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		GameOverWidget = Cast<UGameProjectGameOverWidget>(CreateWidget(GetWorld(),GameOverWidgetClass));
		
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
			PlayerController->SetPause(true);
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AGameProjectGameModeBase::ShowWinWidget(FName NextLevel)
{
	NextLevelName = NextLevel;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		GameWinWidget = Cast<UGameProjectWinWidget>(CreateWidget(GetWorld(),GameWinWidgetClass));
		
		if (GameWinWidget)
		{
			GameWinWidget->AddToViewport();
			PlayerController->SetPause(true);
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
	}
}