// Fill out your copyright notice in the Description page of Project Settings.


#include "PromptUIController.h"

void UPromptUIController::SetPromptText(FString Message)
{
	FText MessageSTR = FText::FromString(Message);
	Message_TB->SetText(MessageSTR);
}
