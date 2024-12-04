// Fill out your copyright notice in the Description page of Project Settings.


#include "TutAttributeComponent.h"

// Sets default values for this component's properties
UTutAttributeComponent::UTutAttributeComponent()
{
	
	Health = 100.f;

}


bool UTutAttributeComponent::IsAlive()const
{
	return Health > 0.f;
}

bool UTutAttributeComponent::ApplyHealthChange(float Delta)
{

	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}


