// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarBehavior.h"
#include "HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarBehavior::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateHealth(1.f, 1.f);
}

void UHealthBarBehavior::UpdateHealth(float Current, float Max)
{
	if (!HealthBar || !HealthText || Max <= 0.f) return;

	const float Percent = Current / Max;
	HealthBar->SetPercent(Percent);

	const FLinearColor Color = Percent <= 0.3f
		? FLinearColor::Red
		: FLinearColor::Green;

	HealthBar->SetFillColorAndOpacity(Color);
	HealthText->SetText(FText::AsNumber(FMath::RoundToInt(Current)));
}

void UHealthBarBehavior::SetHealthComponent(UHealthComponent* HealthComp)
{
	if (!HealthComp) return;

	HealthComponent = HealthComp;

	UpdateHealth(HealthComponent->Health, HealthComponent->MaxHealth);

	HealthComponent->OnHealthChanged.AddDynamic(this, &UHealthBarBehavior::UpdateHealth);

}
