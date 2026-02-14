// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HealthBarBehavior.generated.h"

// Class forward declaration
class UProgressBar;
class UTextBlock;
class UHealthComponent;


/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UHealthBarBehavior : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;

	UPROPERTY()
	TObjectPtr<UHealthComponent> HealthComponent;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealth(float Current, float Max);

public:

	UFUNCTION(BlueprintCallable)
	void SetHealthComponent(UHealthComponent* HealthComp);
	
};
