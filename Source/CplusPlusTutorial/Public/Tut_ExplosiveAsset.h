// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tut_ExplosiveAsset.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class URadialForceComponent;



UCLASS()
class CPLUSPLUSTUTORIAL_API ATut_ExplosiveAsset : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATut_ExplosiveAsset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = "Effects")
	class UNiagaraComponent* NiagaraComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

private:

	UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
