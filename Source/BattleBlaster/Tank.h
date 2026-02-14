// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Tank.generated.h"

class UHealthBarBehavior;
/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext; //Forward Declaration to improve performance

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireInput;

	UPROPERTY(EditAnywhere)
	float MSpeed = 600.0f;

	UPROPERTY(EditAnywhere)
	float RSpeed = 300.0f;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	bool isAlive = true;

	APlayerController* PlayerController;
	
	void Movement(const FInputActionValue& MoveVal);
	void Turn(const FInputActionValue& RotVal);

	void HandleDestruction();
	void SetPlayerEnabled(bool isEnable);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthBarBehavior> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UHealthBarBehavior> HealthBarClass;
};
