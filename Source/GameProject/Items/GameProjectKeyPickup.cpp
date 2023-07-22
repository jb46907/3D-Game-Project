
#include "GameProjectKeyPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

AGameProjectKeyPickup::AGameProjectKeyPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);

	KeySoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
	KeySoundComponent->SetupAttachment(RootComponent);
	KeySoundComponent->SetSound(KeyPickupSound);
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectKeyPickup::OnKeyOverlap);
}

void AGameProjectKeyPickup::OnKeyOverlap(
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
		if (KeyPickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, KeyPickupSound, GetActorLocation());
		}
		switch (KeyType)
		{
		case EKeyType::KeyType1:
			PlayerCharacter->bHasKeyRed = true;
			break;
		case EKeyType::KeyType2:
			PlayerCharacter->bHasKeyBlue = true;
			break;
		case EKeyType::KeyType3:
			PlayerCharacter->bHasKeyGrey = true;
			break;
		}
		Destroy();
	}
}
