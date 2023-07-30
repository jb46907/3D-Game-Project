#include "GameProjectCharacter.h"
#include "GameProjectGameModeBase.h"
#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "Kismet/GameplayStatics.h"

AGameProjectCharacter::AGameProjectCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
	CharacterMesh = FindComponentByClass<USkeletalMeshComponent>();
	
	MoveSpeed = 1.0f;
	FootstepCooldown = 0.0f;
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

	float ForwardValue = GetInputAxisValue(TEXT("MoveForward"));
	float RightValue = GetInputAxisValue(TEXT("MoveRight"));

	if (ForwardValue != 0.0f || RightValue != 0.0f)
	{
		if (ForwardValue > 0.0f && RightValue > 0.0f)
		{
			LastMovementDirection = EMovementDirection::ForwardRight;
		}
		else if (ForwardValue > 0.0f && RightValue < 0.0f)
		{
			LastMovementDirection = EMovementDirection::ForwardLeft;
		}
		else if (ForwardValue < 0.0f && RightValue > 0.0f)
		{
			LastMovementDirection = EMovementDirection::BackwardRight;
		}
		else if (ForwardValue < 0.0f && RightValue < 0.0f)
		{
			LastMovementDirection = EMovementDirection::BackwardLeft;
		}
		else if (ForwardValue > 0.0f)
		{
			LastMovementDirection = EMovementDirection::Forward;
		}
		else if (ForwardValue < 0.0f)
		{
			LastMovementDirection = EMovementDirection::Backward;
		}
		else if (RightValue > 0.0f)
		{
			LastMovementDirection = EMovementDirection::Right;
		}
		else if (RightValue < 0.0f)
		{
			LastMovementDirection = EMovementDirection::Left;
		}
	}

	switch (LastMovementDirection)
	{
	case EMovementDirection::Forward:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
		break;
	case EMovementDirection::ForwardRight:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 315.0f, 0.0f));
		break;
	case EMovementDirection::ForwardLeft:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 225.0f, 0.0f));
		break;
	case EMovementDirection::Backward:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		break;
	case EMovementDirection::BackwardRight:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));
		break;
	case EMovementDirection::BackwardLeft:
		CharacterMesh->SetRelativeRotation(FRotator(0.0f, 135.0f, 0.0f));
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
	// Calculate the combined movement vector and normalize it
	FVector MovementDirection = (GetActorForwardVector() * Value + GetActorRightVector() * GetInputAxisValue(TEXT("MoveRight"))).GetSafeNormal();

	AddMovementInput(MovementDirection, MoveSpeed);

	if (FootstepSoundCue && Value != 0.0f && FootstepCooldown <= 0.0f)
	{
		UGameplayStatics::PlaySound2D(this, FootstepSoundCue);
		FootstepCooldown = 0.8f; // Set a cooldown duration (adjust the value as needed)
	}

	// Reduce the cooldown time each frame (adjust the value as needed)
	FootstepCooldown -= GetWorld()->GetDeltaSeconds();
}

void AGameProjectCharacter::MoveRight(float Value)
{
	// Calculate the combined movement vector and normalize it
	FVector MovementDirection = (GetActorForwardVector() * GetInputAxisValue(TEXT("MoveForward")) + GetActorRightVector() * Value).GetSafeNormal();

	AddMovementInput(MovementDirection, MoveSpeed);

	if (FootstepSoundCue && Value != 0.0f && FootstepCooldown <= 0.0f)
	{
		UGameplayStatics::PlaySound2D(this, FootstepSoundCue);
		FootstepCooldown = 0.8f; // Set a cooldown duration (adjust the value as needed)
	}

	// Reduce the cooldown time each frame (adjust the value as needed)
	FootstepCooldown -= GetWorld()->GetDeltaSeconds();
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