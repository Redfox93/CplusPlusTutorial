// Fill out your copyright notice in the Description page of Project Settings.


#include "TutTargetDummy.h"
#include "TutAttributeComponent.h"

// Sets default values
ATutTargetDummy::ATutTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;

	AttributeComp=CreateDefaultSubobject<UTutAttributeComponent>(TEXT("AttributeComponent"));
	AttributeComp->OnHealthChanged.AddDynamic(this, &ATutTargetDummy::OnHealthChanged);

}


void ATutTargetDummy::OnHealthChanged(AActor* InstigatorActor, UTutAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)

	MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("I'm Getting HIT!"));
}



