#include "GameProjectARotatingButton.h"
#include "GameProject/Game/GameProjectCharacter.h"
#include "GameProjectARotatingPlatform.h"
#include "Kismet/GameplayStatics.h"

AGameProjectARotatingButton::AGameProjectARotatingButton()
{
    PrimaryActorTick.bCanEverTick = false;

    ButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonCollision"));
    RootComponent = ButtonCollision;

    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
    ButtonMesh->SetupAttachment(ButtonCollision);

    ButtonCollision->OnComponentBeginOverlap.AddDynamic(this, &AGameProjectARotatingButton::OnOverlapBegin);

    ButtonSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
    ButtonSoundComponent->SetupAttachment(RootComponent);
    ButtonSoundComponent->SetSound(ButtonSound);
    
    OriginalMeshLocation = ButtonMesh->GetRelativeLocation();
    
    bIsBtnPressed = false;

    ButtonMeshOffsetZ = 40.0f;
    bIsBtnActive = false;
}

void AGameProjectARotatingButton::BeginPlay()
{
    Super::BeginPlay();
}


void AGameProjectARotatingButton::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    AGameProjectCharacter* PlayerCharacter = Cast<AGameProjectCharacter>(OtherActor);
    if (!bIsBtnPressed && !bIsBtnActive)
    {
        bIsBtnActive = true;
        if (PlayerCharacter)
        {
            if (ButtonSound)
            {
                UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, GetActorLocation());
            }
            TArray<AActor*> RotatingPlatforms;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameProjectARotatingPlatform::StaticClass(), RotatingPlatforms);

            for (AActor* Platform : RotatingPlatforms)
            {
                AGameProjectARotatingPlatform* RotatingPlatform = Cast<AGameProjectARotatingPlatform>(Platform);
                if (RotatingPlatform)
                {
                    RotatingPlatform->RotatePlatform();
                }
            }
        }
        GetWorldTimerManager().SetTimer(ButtonActivityTimerHandle, this, &AGameProjectARotatingButton::ResetButtonActivity, 0.5f, false);
        CheckButtonState();
    }
}
void AGameProjectARotatingButton::ResetButtonActivity()
{
    bIsBtnActive = false;
}

void AGameProjectARotatingButton::UpdateButtonLocation(bool bIsPressed)
{
    if (bIsPressed)
    {
        ButtonMesh->SetRelativeLocation(OriginalMeshLocation);
    }
    else
    {
        ButtonMesh->SetRelativeLocation(OriginalMeshLocation + FVector(0, 0, ButtonMeshOffsetZ));
    }
}

void AGameProjectARotatingButton::UpdateButtonState(bool bIsPressed)
{
    if (!bIsPressed)
    {
        UpdateButtonLocation(!bIsPressed);
        bIsBtnPressed = true;
    }
    else
    {
        UpdateButtonLocation(!bIsPressed);
        bIsBtnPressed = false;
    }
}

void AGameProjectARotatingButton::CheckButtonState()
{
    TArray<AActor*> Buttons;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), Buttons);

    for (AActor* button : Buttons)
    {
        AGameProjectARotatingButton* RotatingButton = Cast<AGameProjectARotatingButton>(button);
        if (RotatingButton)
        {
            RotatingButton->UpdateButtonState(RotatingButton->bIsBtnPressed);
        }
    }
}


