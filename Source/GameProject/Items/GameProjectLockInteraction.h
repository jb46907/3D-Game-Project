
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectLockInteraction.generated.h"

UENUM(BlueprintType)
enum class ELockType : uint8
{
	LockType1 UMETA(DisplayName = "RedLock"),
	LockType2 UMETA(DisplayName = "BlueLock"),
	LockType3 UMETA(DisplayName = "GreyLock"),
};

UCLASS()
class GAMEPROJECT_API AGameProjectLockInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameProjectLockInteraction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELockType LockType;

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LockMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* LockSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* LockInteractionSound;

	UFUNCTION()
	void OnDoorOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};