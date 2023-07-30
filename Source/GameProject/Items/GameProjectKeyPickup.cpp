
#include "GameProjectKeyPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

AGameProjectKeyPickup::AGameProjectKeyPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);

	KeySoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
	KeySoundComponent->SetupAttachment(RootComponent);
	KeySoundComponent->SetSound(KeyPickupSound);
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectKeyPickup::OnKeyOverlap);
}

void AGameProjectKeyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementsToActor(DeltaTime);
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

void AGameProjectKeyPickup::AddMovementsToActor(float DeltaTime)
{
	// Yaw rotation (left and right)
	float RotationSpeedYaw = -45.0f;
	float OscillationSpeed = 2.0f;
	float OscillationAmplitude = 15.0f;
	
	FRotator RotationDeltaYaw(0.0f, RotationSpeedYaw * DeltaTime, 0.0f);
	AddActorLocalRotation(RotationDeltaYaw);
	
	FVector NewLocation = GetActorLocation();
	float PitchOffset = FMath::Sin(GetGameTimeSinceCreation() * OscillationSpeed) * OscillationAmplitude;
	NewLocation.Z = 60.0f + PitchOffset; // Adjust the base height (30.0f) as needed
	SetActorLocation(NewLocation);
}

