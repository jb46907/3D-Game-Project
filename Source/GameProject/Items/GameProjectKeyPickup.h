
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectKeyPickup.generated.h"

UENUM(BlueprintType)
enum class EKeyType : uint8
{
	KeyType1 UMETA(DisplayName = "RedKey"),
	KeyType2 UMETA(DisplayName = "BlueKey"),
	KeyType3 UMETA(DisplayName = "GreyKey"),
};

UCLASS()
class GAMEPROJECT_API AGameProjectKeyPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameProjectKeyPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EKeyType KeyType;

	virtual void Tick(float DeltaTime) override;

	void AddMovementsToActor(float DeltaTime);

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* KeyMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* KeySoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* KeyPickupSound;
	
	UFUNCTION()
	void OnKeyOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};