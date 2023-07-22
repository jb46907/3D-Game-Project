
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectARotatingPlatform.generated.h"

UCLASS()
class GAMEPROJECT_API AGameProjectARotatingPlatform : public AActor
{
public:
	AGameProjectARotatingPlatform();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* PlatformCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float RotationAngle = 90.0f;

	UFUNCTION()
	void RotatePlatform();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* PlatformSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* PlatformSound;

private:
	GENERATED_BODY()
	
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	FRotator OriginalMeshRotation;
	
	FRotator TargetRotation;
	
	bool bIsRotating;
};
