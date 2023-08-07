#include "GameProjectTrapBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"


AGameProjectTrapBase::AGameProjectTrapBase()
{
    PrimaryActorTick.bCanEverTick = false;
    
    TrapCollision = CreateDefaultSubobject<UBoxComponent>("TrapCollision");
    RootComponent = TrapCollision;
    
    TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>("TrapMesh");
    TrapMesh->SetupAttachment(TrapCollision);

    TrapSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
    TrapSoundComponent->SetupAttachment(RootComponent);
    TrapSoundComponent->SetSound(TrapSound);
    
    OriginalMeshLocation = TrapMesh->GetRelativeLocation();
    
    bTrapActive = false;
    bTrapTriggered = false;
    TrapMeshOffsetZ = 30.0f;
    
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
    AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
    if (!bTrapActive)
    {
        if (PlayerCharacter)
        {
            bTrapActive = true;
        }
    }
    else
    {
        if (PlayerCharacter && bTrapTriggered)
        {
            PlayerCharacter->Die();
            bTrapTriggered = false;
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
        TrapMesh->SetRelativeLocation(OriginalMeshLocation + FVector(0,0,TrapMeshOffsetZ));
        bTrapTriggered = true;
    }
}
