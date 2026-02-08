// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "EnemyTower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankGameInstance.h"


void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	TArray <AActor*> Enemies;

	//Finding and placing all enemies in an array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTower::StaticClass(), Enemies);
	EnemyCount = Enemies.Num();
	UE_LOG(LogTemp, Display, TEXT("No. of enemies in scene: %d"), EnemyCount);

	//Single player game always has index 0 for the player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (Tank == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Game Manager faild to find the Tank"));
		}
	}

	int32 LoopIndex = 0;
	while (LoopIndex < EnemyCount)
	{
		// Saving the enemy's game object that was found in particular index
		AActor* EnemyActor = Enemies[LoopIndex];
		// if enemy game object is not null
		if (EnemyActor)
		{
			// cast the tower to actor
			AEnemyTower* EnemyTower = Cast<AEnemyTower>(EnemyActor);
			if (EnemyTower) 
			{
				// The tank on the left side is the one that is inside the Enemytower.cpp file and on the right side is the one that is declared above in this .cpp file
				EnemyTower->Tank = Tank;
				UE_LOG(LogTemp, Display, TEXT("%s setting the tank variable"), *EnemyTower->GetActorNameOrLabel());
			}
		}
		
		LoopIndex++;
	}

	// Getting the player controller from the world and the index of the player
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// If the controller is valid, show the message which will be returned by the Message variable
		Message = CreateWidget<UPromptUIController>(PlayerController, PromptUIClass);

		// If the message is valid, add the text to the player's screen 
		if (Message)
		{
			Message->AddToPlayerScreen();

			//Assigning the string to the variable
			Message->SetPromptText("Get Ready!");
		}
	}
	
	CountdownInSec = GameStrtDelay;
	GetWorldTimerManager().SetTimer(GameStartDelayHandler, this, &AGameManager::OnGameStartTimeOut, 1.0f, true);
}

void AGameManager::OnGameStartTimeOut()
{
	CountdownInSec--;
	if (CountdownInSec > 0)
	{
		Message->SetPromptText(FString::FromInt(CountdownInSec));
	}
	else if (CountdownInSec == 0)
	{
		Message->SetPromptText("GO!");
		Tank->SetPlayerEnabled(true);
	}
	else
	{
		// To Reset the timer so that it doesn't go negative
		GetWorldTimerManager().ClearTimer(GameStartDelayHandler);
		Message->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameManager::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;
	
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		AEnemyTower* DeadEnemy = Cast<AEnemyTower>(DeadActor);
		if (DeadEnemy)
		{
			DeadEnemy->HandleDestruction();

			EnemyCount--;
			if (EnemyCount == 0)
			{
				IsGameOver = true;
				Victory = true;
			}
		}
	}

	if (IsGameOver)
	{
		// Ternary Opeartion to display Victory/Defeat
		FString GameOverText = Victory ? "Victory!" : "Defeat!";
		Message->SetPromptText(GameOverText);
		Message->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle GameOverTimeHandler;
		GetWorldTimerManager().SetTimer(GameOverTimeHandler, this, &AGameManager::OnGameOverTimeOut, GameOverDelay, false);
	}
}

void AGameManager::OnGameOverTimeOut()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UToonTankGameInstance* ToonTankGI = Cast< UToonTankGameInstance>(GameInstance);
		if (ToonTankGI)
		{
			if (Victory)
			{
				// Load Next Level
				ToonTankGI->LoadNextLevel();
			}
			else
			{
				ToonTankGI->RestartCurrentLevel();
			}
		}
	}
}


