// Fill out your copyright notice in the Description page of Project Settings.

#include "Tut_MagicProjectile.h"
#include "TutBaseProjectile.h"


// Sets default values
ATut_MagicProjectile::ATut_MagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

