// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PromptUIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UPromptUIController : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Message_TB; // Must be the same name as in the editor

	void SetPromptText(FString Message);
	
};
