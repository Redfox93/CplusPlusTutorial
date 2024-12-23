// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;
class ACharacter;
class USoundBase;

UCLASS()
class CPLUSPLUSTUTORIAL_API ATutBaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATutBaseProjectile();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void CalculateProjectileDirection();

	UFUNCTION(BlueprintCallable, Category = "ExplosionEffect")
	void CallExplosion();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Projectle")
	float MaxRayCastDistance = 10000.f; // (100~mt)

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "1 - Effects", meta = (DisplayPriority = 0));
	UNiagaraComponent* ProjectileEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2 - Effects", meta = (DisplayName = " ImpactEffect", ToolTip = "Expodes on impact", DisplayPriority = 1));
	UNiagaraSystem* ImpactEffect;

	UPROPERTY(VisibleAnywhere, Category ="Audio")
	UAudioComponent* ProjectileLoop;

	UPROPERTY(EditAnywhere, Category ="Audio")
	USoundBase* ProjectileImpact;

	UPROPERTY(VisibleAnywhere)
	ACharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
};
