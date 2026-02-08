// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameInstance.h"
#include "Kismet/Gameplaystatics.h"

void UToonTankGameInstance::ChangeLevel(int32 Index)
{
	if (Index > 0 && Index <= LastLvlIndex)
	{
		CurrLvlIndex = Index;

		FString LevelName = FString::Printf(TEXT("Level_%d"), CurrLvlIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
	}
}

void UToonTankGameInstance::LoadNextLevel()
{
	if (CurrLvlIndex < LastLvlIndex)
	{
		ChangeLevel(CurrLvlIndex + 1);
	}
	else
	{
		RestartGame();
	}
}
void UToonTankGameInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrLvlIndex);
}
void UToonTankGameInstance::RestartGame()
{
	ChangeLevel(1);
}
