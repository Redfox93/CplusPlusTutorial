// Fill out your copyright notice in the Description page of Project Settings.


#include "TutAttributeComponent.h"

// Sets default values for this component's properties
UTutAttributeComponent::UTutAttributeComponent()
{
	MaxHealth = 100.f;
	Health = FMath::Clamp(MaxHealth, 0.f, MaxHealth);
	
}


bool UTutAttributeComponent::IsAlive()const
{
	return Health > 0.f;
}

bool UTutAttributeComponent::ApplyHealthChange(float Delta)
{

	Health += Delta;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}


