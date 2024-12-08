#include "TutInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "TutAttributeComponent.h"
#include "TimerManager.h"

// Sets default values
ATutInteractable::ATutInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>("SphereCollisionComp");
	SphereCollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollisionComp->SetGenerateOverlapEvents(true);
	SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATutInteractable::OnActorOverlap);
	SphereCollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATutInteractable::OnActorEndOverlap);

	RootComponent = SphereCollisionComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComp->SetupAttachment(RootComponent);

	Interactable = false;
}

void ATutInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void ATutInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATutInteractable::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interactable = true;
}

void ATutInteractable::OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Interactable = false;
}

void ATutInteractable::Interact_Implementation(APawn* InstigatorPawn)
{
	if (Interactable && InstigatorPawn)
	{
		UTutAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<UTutAttributeComponent>();
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(+20.f);
		}

		FTimerDelegate DamageDelegate;
		DamageDelegate.BindUFunction(this, FName("HandleInteraction"), false);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_DeactivateTimer, DamageDelegate, 0.1f, false);

		FTimerDelegate RevertDelegate;
		RevertDelegate.BindUFunction(this, FName("HandleInteraction"), true);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ActivateTimer, RevertDelegate, 2.0f, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Object not interactable."));
	}
}

void ATutInteractable::HandleInteraction(bool InteractionCondition)
{
	Interactable = InteractionCondition;
	SphereCollisionComp->SetGenerateOverlapEvents(InteractionCondition);
	StaticMeshComp->SetVisibility(InteractionCondition);
}
