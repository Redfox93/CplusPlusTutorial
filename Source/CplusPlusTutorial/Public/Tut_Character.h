// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Tut_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTutInteractionComponent;
class UAnimMontage;
class UTutAttributeComponent;

UCLASS()
class CPLUSPLUSTUTORIAL_API ATut_Character : public  ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> TertiaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	AActor* SpawnedProjectile;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_TertiaryAttack;

public:
	// Sets default values for this character's properties
	ATut_Character();

protected:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UTutInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTutAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UTutAttributeComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION()
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	// Input functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void StopRun(const FInputActionValue& Value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack();
	void TertiaryAttack();
	void TertiaryAttack_TimeElapsed();
	void TertiaryAttack_TimerTeleport();
	void PrimaryInteract();

};
