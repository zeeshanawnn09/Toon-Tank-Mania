// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATank::ATank()
{

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	// Start here - Base code for default mapping context
	PlayerController = Cast < APlayerController>(Controller);
	if (PlayerController)
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}

		}
	} // ends here

	// To disable the player at the start of the game
	SetPlayerEnabled(false);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);

		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.0f, 15, FColor::Cyan);
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ATank::Movement);
		EIC->BindAction(RotateInput, ETriggerEvent::Triggered, this, &ATank::Turn);
		EIC->BindAction(FireInput, ETriggerEvent::Started, this, &ATank::FireBehavior);
	}
}

void ATank::Movement(const FInputActionValue& MoveVal)
{
	float InputValue = MoveVal.Get<float>();

	// function to move the tank in local space
	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	DeltaLocation.X = MSpeed * InputValue * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const FInputActionValue& RotVal)
{
	float InputValue = RotVal.Get<float>();

	// function to rotate the tank in local space
	FRotator DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
	DeltaRotation.Yaw = RSpeed * InputValue * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);

// Disabling Input Handling
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);

	isAlive = false;
}

void ATank::SetPlayerEnabled(bool isEnable)
{
	if (PlayerController)
	{
		if (isEnable)
		{
			EnableInput(PlayerController);
		}
		else
		{
			DisableInput(PlayerController);	
		}
		PlayerController->bShowMouseCursor = isEnable;
	}
}



