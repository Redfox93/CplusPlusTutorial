// Fill out your copyright notice in the Description page of Project Settings.

#include "Tut_MagicProjectile.h"
#include "TutBaseProjectile.h"
#include "Engine/StaticMeshActor.h"
#include "PhysicsEngine/RadialForceComponent.h"



// Sets default values
ATut_MagicProjectile::ATut_MagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RadialComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialComponent"));
	RadialComp->SetupAttachment(GetRootComponent());
	
	if (TargetTag.IsNone())
	{
		TargetTag = FName("Destructible");
	}
	
}

// Called when the game starts or when spawned
void ATut_MagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATut_MagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RadialComp->FireImpulse();

	

}

void ATut_MagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnActorOverlap(OverlappedComponent,OtherActor,OtherComp,OtherBodyIndex,bFromSweep,SweepResult);

	if (!OtherActor)
	{
		return;
	}

	if (AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(OtherActor))
	{
		if (StaticMeshActor->Tags.Contains(TargetTag))
		{
			StaticMeshActor->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("DESTROYING ACTOR"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor does not have the target tag."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping actor is not a Static Mesh Actor."));
	}
}