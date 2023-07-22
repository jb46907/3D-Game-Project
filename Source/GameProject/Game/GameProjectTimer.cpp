#include "GameProjectTimer.h"

#include "GameProjectCharacter.h"
#include "GameProjectWidget.h"
#include "Kismet/GameplayStatics.h"


AGameProjectTimer::AGameProjectTimer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TimerDuration = 300.0f;
	ElapsedTime = 0.0f;
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
		ElapsedTime = 0.0f;
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
	return ElapsedTime;
}

void AGameProjectTimer::TimerCallback()
{
	ElapsedTime += 1.0f;
	if (ElapsedTime >= TimerDuration)
	{
		AGameProjectCharacter* ProjectCharacter = Cast<AGameProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ProjectCharacter)
		{
			StopTimer();
			ProjectCharacter->Die();
		}
	}
}
