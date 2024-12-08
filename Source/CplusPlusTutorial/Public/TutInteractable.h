#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TutInteractable.generated.h"

// Forward declaration of classes
class UStaticMeshComponent;
class USphereComponent;

/**
 * AInteractable class that implements ITutGameplayInterface for interaction logic
 */
UCLASS()
class CPLUSPLUSTUTORIAL_API ATutInteractable : public AActor, public ITutGameplayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATutInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ITutGameplayInterface implementation
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	/** Called when an actor overlaps with the sphere component */
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Called when an actor stops overlapping the sphere component */
	UFUNCTION()
	void OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Handles enabling or disabling interaction effects */
	UFUNCTION()
	void HandleInteraction(bool InteractionCondition);

private:
	/** Static mesh component for visual representation */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	/** Sphere collision component for detecting overlaps */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollisionComp;

	/** Tracks whether the object is interactable */
	UPROPERTY()
	bool Interactable;

	/** Timer handle for deactivating interaction effects */
	FTimerHandle TimerHandle_DeactivateTimer;

	/** Timer handle for reactivating interaction effects */
	FTimerHandle TimerHandle_ActivateTimer;
};
