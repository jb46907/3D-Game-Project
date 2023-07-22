
#include "GameProjectGameModeBase.h"

#include "GameProjectCharacter.h"
#include "GameProjectTimer.h"
#include "GameProjectWidget.h"
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
		// Start the timer when the level begins
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