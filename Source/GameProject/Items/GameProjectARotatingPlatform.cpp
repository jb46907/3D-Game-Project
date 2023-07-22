
#include "GameProjectARotatingPlatform.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "Kismet/GameplayStatics.h"


AGameProjectARotatingPlatform::AGameProjectARotatingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    PlatformCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformCollision"));
    RootComponent = PlatformCollision;
    
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    PlatformMesh->SetupAttachment(PlatformCollision);

    PlatformSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
    PlatformSoundComponent->SetupAttachment(RootComponent);
    PlatformSoundComponent->SetSound(PlatformSound);
    
    PlatformCollision->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectARotatingPlatform::OnOverlapBegin);
    PlatformCollision->OnComponentEndOverlap.AddDynamic(this, &AGameProjectARotatingPlatform::OnOverlapEnd);
    
    OriginalMeshRotation = PlatformMesh->GetRelativeRotation();
    TargetRotation = FRotator(0, RotationAngle, 0);
    bIsRotating = false;
}

void AGameProjectARotatingPlatform::BeginPlay()
{
    Super::BeginPlay();
}

void AGameProjectARotatingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGameProjectARotatingPlatform::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        bIsRotating = true;
    }
}

void AGameProjectARotatingPlatform::OnOverlapEnd(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
    if (bIsRotating && PlayerCharacter)
    {
        if (PlatformSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, PlatformSound, GetActorLocation());
        }
        PlatformMesh->SetRelativeRotation(OriginalMeshRotation + TargetRotation);
        RotationAngle += 90.0f;
        TargetRotation = FRotator(0, RotationAngle, 0);
        bIsRotating = false;
    }
}

void AGameProjectARotatingPlatform::RotatePlatform()
{
    PlatformMesh->SetRelativeRotation(OriginalMeshRotation + TargetRotation);
    RotationAngle += 90.0f;
    TargetRotation = FRotator(0, RotationAngle, 0);
}
