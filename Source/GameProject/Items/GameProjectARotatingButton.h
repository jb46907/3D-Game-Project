#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectARotatingButton.generated.h"

UCLASS()
class GAMEPROJECT_API AGameProjectARotatingButton : public AActor
{
	GENERATED_BODY()

public:
	AGameProjectARotatingButton();

protected:
	virtual void BeginPlay() override;

	FVector OriginalMeshLocation;
	FTimerHandle ButtonActivityTimerHandle;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* ButtonSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* ButtonSound;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* ButtonCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ButtonMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button Settings")
	bool bIsBtnPressed;

	UPROPERTY(EditDefaultsOnly, Category = "Button Settings")
	float ButtonMeshOffsetZ;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void CheckButtonState();

	UFUNCTION()
	void UpdateButtonLocation(bool bIsPressed);
	
	UFUNCTION()
	void UpdateButtonState(bool bIsPressed);

	UFUNCTION()
	void ResetButtonActivity();

private:
	FVector NewMeshLocation;
	bool bIsBtnActive;
	
};
