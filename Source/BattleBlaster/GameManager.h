// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PromptUIController.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API AGameManager : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATank* Tank;
	int32 EnemyCount;
	int32 CountdownInSec;
	bool Victory = false;

	UPromptUIController* Message;
	FTimerHandle GameStartDelayHandler;

	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;

	UPROPERTY(EditAnywhere)
	int32 GameStrtDelay = 4;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPromptUIController> PromptUIClass;

	void ActorDied(AActor* DeadActor);

	void OnGameOverTimeOut();
	void OnGameStartTimeOut();
	
};
