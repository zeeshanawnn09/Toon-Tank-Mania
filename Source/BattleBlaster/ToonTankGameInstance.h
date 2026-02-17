// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "ToonTankGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UToonTankGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 LastLvlIndex = 3;
	
	UPROPERTY(VisibleAnywhere)
	int32 CurrLvlIndex = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	USoundBase* BackgroundMusic;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;

	void LoadNextLevel();
	void RestartCurrentLevel();
	void RestartGame();
	virtual void Init() override;

private:
	void ChangeLevel(int32 Index);
};
