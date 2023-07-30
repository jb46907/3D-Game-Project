
#include "GameProjectItemBase.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "GameProject/Game/GameProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"


AGameProjectItemBase::AGameProjectItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	CoinSoundComponent = CreateDefaultSubobject<UAudioComponent>("CoinSoundComponent");
	CoinSoundComponent->SetupAttachment(RootComponent);
	CoinSoundComponent->SetSound(CoinSound);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->Deactivate();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectItemBase::OverLapBegin);
	
}

void AGameProjectItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGameProjectItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddRotationToActor(DeltaTime);
}

void AGameProjectItemBase::OverLapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AGameProjectGameModeBase* GameMode = Cast<AGameProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if(Cast<AGameProjectCharacter>(OtherActor))
	{
		if (CoinSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CoinSound, GetActorLocation());
		}
		if (NiagaraComponent && NiagaraComponent->IsValidLowLevel())
		{
			NiagaraComponent->SetWorldLocation(Mesh->GetRelativeLocation());
				
			if (!NiagaraComponent->IsActive())
			{
				NiagaraComponent->Activate();
			}
		}
		GameMode->ItemCollected();
		Destroy();
	}
}

void AGameProjectItemBase::AddRotationToActor(float DeltaTime)
{
	float RotationSpeed = 45.0f;
	FRotator RotationDelta(0.0f, RotationSpeed * DeltaTime, 0.0f);
	AddActorLocalRotation(RotationDelta);
}