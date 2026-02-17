// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameInstance.h"
#include "Kismet/Gameplaystatics.h"

void UToonTankGameInstance::Init()
{
	Super::Init();

	if (BackgroundMusic)
	{
		AudioComp = UGameplayStatics::CreateSound2D(GetWorld(), BackgroundMusic, 0.5f, 1.0f, 0.0f, nullptr, true);

		if (AudioComp)
		{
			AudioComp->Play();
		}
	}
}

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
