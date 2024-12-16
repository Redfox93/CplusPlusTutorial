// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TutAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

// Sets default values
ATutAICharacter::ATutAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create Perception Component
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));

	// Create and configure Sight sense
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.0f;
	SightConfig->LoseSightRadius = 2200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 0.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;   // Important to detect actors
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// Assign the sense configuration to the Perception Component
	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ATutAICharacter::OnPerceptionUpdated);
}

void ATutAICharacter::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		// Check if the actor is a pawn we want to consider as an enemy
		if (APawn* EnemyPawn = Cast<APawn>(Actor))
		{
			FActorPerceptionBlueprintInfo Info;
			AIPerceptionComp->GetActorsPerception(Actor, Info);

			for (auto& Stimulus : Info.LastSensedStimuli)
			{
				if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>() && Stimulus.WasSuccessfullySensed())
				{
					
					OnPawnSeen(EnemyPawn);
					FString PawnName = EnemyPawn->GetName();
					UE_LOG(LogTemp, Warning, TEXT("On Perception Updated:%s"), *PawnName);
					break;
				}
			}
		}
	}
}

void ATutAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsObject("TargetActor", Pawn);
		}

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

