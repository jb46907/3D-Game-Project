#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectTrapBase.generated.h"

UCLASS()
class GAMEPROJECT_API AGameProjectTrapBase : public AActor
{
	GENERATED_BODY()

public:
	AGameProjectTrapBase();
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* TrapCollision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* TrapMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Trap")
	bool bTrapActive;

	bool bTrapTriggered;

	UPROPERTY(EditDefaultsOnly, Category = "Trap")
	float TrapMeshOffsetZ;
	
	FVector OriginalMeshLocation;
	
	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* TrapSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* TrapSound;
	
	UFUNCTION()
	void OnTrapOverlapBegin(
		class UPrimitiveComponent* OverlappedComponent,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTrapOverlapEnd(
		class UPrimitiveComponent* OverlappedComponent,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
