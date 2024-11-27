// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutGameplayInterface.h"
#include "TutItemChestClass.generated.h"

class UStaticMeshComponent;


UCLASS()
class CPLUSPLUSTUTORIAL_API ATutItemChestClass : public AActor, public ITutGameplayInterface
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ATutItemChestClass();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
