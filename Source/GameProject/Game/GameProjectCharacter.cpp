#include "GameProjectCharacter.h"
#include "GameProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGameProjectCharacter::AGameProjectCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetCapsuleComponent());
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());

	FootStepSoundComponent = CreateDefaultSubobject<UAudioComponent>("ButtonSoundComponent");
	FootStepSoundComponent->SetupAttachment(RootComponent);
	FootStepSoundComponent->SetSound(FootStepSound);
	
	CharacterMesh = FindComponentByClass<USkeletalMeshComponent>();
	
	MoveSpeed = 500.0f;

	bHasKeyRed = false;
	bHasKeyBlue = false;
	bHasKeyGrey = false;
	bTimesUp = false;

	Pausing = false;
}

void AGameProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	RespawnLocation = GetActorLocation();
	RespawnRotation = GetActorRotation();
}

void AGameProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AGameProjectGameModeBase* GameMode = Cast<AGameProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->UpdateTimer();
	if(Pausing)
	{
		 
	}

	switch (LastMovementDirection)
	{
	case EMovementDirection::Forward:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
		break;
	case EMovementDirection::Backward:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		break;
	case EMovementDirection::Left:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		break;
	case EMovementDirection::Right:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}
}

// Called to bind functionality to input
void AGameProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGameProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGameProjectCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("PauseGame"), IE_Pressed,this, &AGameProjectCharacter::CheckPause);
}

void AGameProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		LastMovementDirection = Value > 0.0f ? EMovementDirection::Forward : EMovementDirection::Backward;
	}
	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void AGameProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		LastMovementDirection = Value > 0.0f ? EMovementDirection::Right : EMovementDirection::Left;
	}
	AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
}

void AGameProjectCharacter::CheckPause()
{
	if(Pausing)
	{
		Pausing = false;
	}
	else
	{
		Pausing = true;
	}
}

void AGameProjectCharacter::Die()
{
	AGameProjectGameModeBase* GameMode = Cast<AGameProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
		UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName), true);
	}
}

void AGameProjectCharacter::RespawnPlayer()
{
	SetActorLocation(RespawnLocation);
}