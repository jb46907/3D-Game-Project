#include "GameProjectTrapBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"


AGameProjectTrapBase::AGameProjectTrapBase()
{
    PrimaryActorTick.bCanEverTick = false;
    
    TrapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("TrapCollision"));
    RootComponent = TrapCollision;
    
    TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
    TrapMesh->SetupAttachment(TrapCollision);
    
    OriginalMeshLocation = TrapMesh->GetRelativeLocation();
    
    bTrapActive = false;
    bTrapTriggered = true;
    TrapMeshOffsetZ = -40.0f;

    FVector NewMeshLocation = TrapMesh->GetRelativeLocation();
    NewMeshLocation.Z = TrapMeshOffsetZ;
    TrapMesh->SetRelativeLocation(NewMeshLocation);

    TrapSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
    TrapSoundComponent->SetupAttachment(RootComponent);
    TrapSoundComponent->SetSound(TrapSound);
    
    TrapCollision->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectTrapBase::OnTrapOverlapBegin);
    TrapCollision->OnComponentEndOverlap.AddDynamic(this, &AGameProjectTrapBase::OnTrapOverlapEnd);
}

void AGameProjectTrapBase::BeginPlay()
{
    Super::BeginPlay();
}

void AGameProjectTrapBase::OnTrapOverlapBegin(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!bTrapActive)
    {
        AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            bTrapActive = true;
        }
    }
    else
    {
        AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
        if (PlayerCharacter && !bTrapTriggered)
        {
            PlayerCharacter->Die();
            bTrapTriggered = true;
        }
    }
}

void AGameProjectTrapBase::OnTrapOverlapEnd(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (bTrapActive && OtherActor && OtherActor->IsA<AGameProjectCharacter>())
    {
        if (TrapSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, TrapSound, GetActorLocation());
        }
        TrapMesh->SetRelativeLocation(OriginalMeshLocation);
        bTrapTriggered = false;
    }
}
