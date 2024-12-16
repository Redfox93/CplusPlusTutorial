// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TutAICharacter.generated.h"


UCLASS()
class CPLUSPLUSTUTORIAL_API ATutAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutAICharacter();

protected:


	//virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	UAISenseConfig_Sight* SightConfig;

	// This function is called when perception updates (can be multiple actors)
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);


public:

};
