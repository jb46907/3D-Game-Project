
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectFinish.generated.h"

UCLASS()
class GAMEPROJECT_API AGameProjectFinish : public AActor
{
	GENERATED_BODY()

public:
	AGameProjectFinish();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* FinishSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FinishSound;

	UFUNCTION()
	void OverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	FName NextLevelName;
};
