#include "GameProjectTimer.h"

#include "GameProjectCharacter.h"
#include "GameProjectWidget.h"
#include "Kismet/GameplayStatics.h"


AGameProjectTimer::AGameProjectTimer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	EndDuration = 0.0f;
	TimerDuration = 300.0f;
	bTimerRunning = false;
}

void AGameProjectTimer::BeginPlay()
{
	Super::BeginPlay();
}

void AGameProjectTimer::StartTimer()
{
	if (!bTimerRunning)
	{
		bTimerRunning = true;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameProjectTimer::TimerCallback, 1.0f, true);
	}
}


void AGameProjectTimer::StopTimer()
{
	if (bTimerRunning)
	{
		bTimerRunning = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

int AGameProjectTimer::GetElapsedTime() const
{
	return TimerDuration;
}

void AGameProjectTimer::TimerCallback()
{
	TimerDuration -= 1.0f;
	if (TimerDuration <= EndDuration)
	{
		AGameProjectCharacter* ProjectCharacter = Cast<AGameProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ProjectCharacter)
		{
			StopTimer();
			ProjectCharacter->Die();
		}
	}
}
