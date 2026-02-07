// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTower.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireTimeHandler;

	//Enemy shall fire every 2 seconds
	GetWorldTimerManager().SetTimer(FireTimeHandler, this, &AEnemyTower::CanFire, FireRate, true);
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void AEnemyTower::CanFire()
{
	if (Tank && Tank->isAlive &&IsInRange())
	{
		FireBehavior();
	}
}

bool AEnemyTower::IsInRange()
{
	bool Result = false;
	//if tank is valid
	if (Tank)
	{
		float Dist2Tank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		Result = (Dist2Tank <= FireRange);
	}
	return Result;
}

void AEnemyTower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
