// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TutAIController.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSPLUSTUTORIAL_API ATutAIController : public AAIController
{
	GENERATED_BODY()

protected:

UPROPERTY(EditDefaultsOnly, Category = "AI")

UBehaviorTree* BehaviorTree;

virtual void BeginPlay();
	
};
