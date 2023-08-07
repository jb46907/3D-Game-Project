
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameProjectTimer.generated.h"

UCLASS()
class GAMEPROJECT_API AGameProjectTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGameProjectTimer();
	
	void StartTimer();
	
	void StopTimer();
	
	int GetElapsedTime() const;


protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void TimerCallback();


private:
	UPROPERTY(EditAnywhere)
	float EndDuration;

	FTimerHandle TimerHandle;
	
	int TimerDuration;
	
	bool bTimerRunning;
};
