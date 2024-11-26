// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tut_MagicProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;


UCLASS()
class CPLUSPLUSTUTORIAL_API ATut_MagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATut_MagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraComponent* NiagaraComponent;


};
