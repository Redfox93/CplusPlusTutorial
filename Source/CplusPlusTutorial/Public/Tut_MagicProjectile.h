// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutBaseProjectile.h"
#include "Tut_MagicProjectile.generated.h"




class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class URadialForceComponent;



UCLASS()
class CPLUSPLUSTUTORIAL_API ATut_MagicProjectile : public ATutBaseProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATut_MagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	URadialForceComponent* RadialComp;

public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	private:
    // The tag to check for
    UPROPERTY(EditAnywhere, Category = "Tag")
    FName TargetTag;
};

