
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "GameProjectItemBase.generated.h"

UCLASS()
class GAMEPROJECT_API AGameProjectItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameProjectItemBase();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;

	virtual void Tick(float DeltaTime) override;
	
	void AddRotationToActor(float DeltaTime);

	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* CoinSoundComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* CoinSound;

	UPROPERTY(EditAnywhere, Category = "Particles")
	UNiagaraComponent* NiagaraComponent;
};
