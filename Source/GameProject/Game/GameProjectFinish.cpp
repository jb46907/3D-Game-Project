
#include "GameProjectFinish.h"

#include "GameProjectGameModeBase.h"
#include "GameProjectTimer.h"
#include "Components/BoxComponent.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

AGameProjectFinish::AGameProjectFinish()
{
	PrimaryActorTick.bCanEverTick = false;

	UBoxComponent* CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	FinishSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
	FinishSoundComponent->SetupAttachment(RootComponent);
	FinishSoundComponent->SetSound(FinishSound);
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectFinish::OverlapBegin);
}

void AGameProjectFinish::BeginPlay()
{
	Super::BeginPlay();
}

void AGameProjectFinish::OverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	AGameProjectCharacter* Character = Cast<AGameProjectCharacter>(OtherActor);
	if (Character)
	{
		if (FinishSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FinishSound, GetActorLocation());
		}	
		AGameProjectGameModeBase* GameMode = Cast<AGameProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode && GameMode->AreAllItemsCollected())
		{
			GameMode->StopTimer();
			const FString NextLevelString = NextLevelName.ToString();
			if (!NextLevelString.IsEmpty())
			{
				UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
			}
		}
	}
}