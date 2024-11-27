// Fill out your copyright notice in the Description page of Project Settings.


#include "Tut_ExplosiveAsset.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "NiagaraComponent.h"
#include "Tut_MagicProjectile.h"


// Sets default values
ATut_ExplosiveAsset::ATut_ExplosiveAsset()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->ForceStrength = 1000.f;
	RadialForceComp->Radius = 500.f;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComp->SetAutoActivate(false);
	NiagaraComp->SetupAttachment(StaticMeshComp);

}

// Called when the game starts or when spawned
void ATut_ExplosiveAsset::BeginPlay()
{
	Super::BeginPlay();

    StaticMeshComp->OnComponentHit.AddDynamic(this, &ATut_ExplosiveAsset::OnHit);
	
}

// Called every frame
void ATut_ExplosiveAsset::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATut_ExplosiveAsset::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // Check if the OtherActor is of type ATut_MagicProjectile
    if (ATut_MagicProjectile* MagicProjectile = Cast<ATut_MagicProjectile>(OtherActor))
    {
        // Ensure it is not this actor (although this check may not be needed if the projectile is always a different actor)
        if (OtherActor != this)
        {
            // Apply the radial force if the component and force strength are valid
            if (RadialForceComp && RadialForceComp->IsActive())
            {
                RadialForceComp->FireImpulse();
               
                UE_LOG(LogTemp, Error, TEXT("ImpulseFired!"));
            }

            // Activate the Niagara effect if available
            if (NiagaraComp)
            {
                NiagaraComp->ActivateSystem();
            }
        }
    }
}

