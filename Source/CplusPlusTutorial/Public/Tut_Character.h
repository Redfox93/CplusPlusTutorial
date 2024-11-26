// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Tut_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTutInteractionComponent

UCLASS()
class CPLUSPLUSTUTORIAL_API ATut_Character : public  ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	ATut_Character();

protected:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;


	//IMPLEMENT BINDING! LIKE "F" FOR INTERACT
	UPROPERTY(VisibleAnywhere)
	UTutInteractionComponent* InteractionComp;

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

};
