
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectCharacter.generated.h"


UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right
};

UCLASS()
class GAMEPROJECT_API AGameProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AGameProjectCharacter();
	void Die();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* FootStepSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FootStepSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EMovementDirection LastMovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* CharacterMesh;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void CheckPause();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasKeyRed = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasKeyBlue = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasKeyGrey = false;

	UPROPERTY()
	bool Pausing;
	
	UPROPERTY()
	bool bTimesUp;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void RespawnPlayer();

	UPROPERTY(EditAnywhere, Category = "Character")
	FVector RespawnLocation;
	
	UPROPERTY(EditAnywhere, Category = "Character")
	FRotator RespawnRotation;
	
};

