// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;

UCLASS()
class CPLUSPLUSTUTORIAL_API ATutBaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATutBaseProjectile();


	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void CalculateProjectileDirection();

	UFUNCTION(BlueprintImplementableEvent, Category = "ExplosionEffect")
	void CallExplosion();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Projectle")
	float MaxRayCastDistance = 10000.f; // (100~mt)

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraComponent* NiagaraComponent;
};
