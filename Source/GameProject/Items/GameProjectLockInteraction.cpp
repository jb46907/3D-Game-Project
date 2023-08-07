
#include "GameProjectLockInteraction.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

AGameProjectLockInteraction::AGameProjectLockInteraction()
{
	PrimaryActorTick.bCanEverTick = false;

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	RootComponent = LockMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);

	LockSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
	LockSoundComponent->SetupAttachment(RootComponent);
	LockSoundComponent->SetSound(LockInteractionSound);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectLockInteraction::OnDoorOverlap);
}

void AGameProjectLockInteraction::OnDoorOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		switch (LockType)
		{
		case ELockType::LockType1:
			if (PlayerCharacter->bHasKeyRed)
			{
				PlayerCharacter->bHasKeyRed = false;
				if (LockInteractionSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, LockInteractionSound, GetActorLocation());
				}
				Destroy();
			}
			break;
		case ELockType::LockType2:
			if (PlayerCharacter->bHasKeyBlue)
			{
				PlayerCharacter->bHasKeyBlue = false;
				if (LockInteractionSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, LockInteractionSound, GetActorLocation());
				}
				Destroy();
			}
			break;
		case ELockType::LockType3:
			if (PlayerCharacter->bHasKeyGrey)
			{
				PlayerCharacter->bHasKeyGrey = false;
				if (LockInteractionSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, LockInteractionSound, GetActorLocation());
				}
				Destroy();
			}
			break;
		}
	}
}

