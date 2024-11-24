// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterControllerBase.generated.h"

class UInputMappingContext;
class UInputAction;
class ACharacterBase;

struct FInputActionValue;

UCLASS()
class CPLUSPLUSTUTORIAL_API ACharacterControllerBase : public APlayerController
{
    GENERATED_BODY()

public:
    // Constructor
    ACharacterControllerBase();

    // Overrides
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

protected:
    // Input Mapping Context
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TWA_Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> CurrentMappingContext;

    // Input Actions
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TWA_Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TWA_Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TWA_Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TWA_Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> RunAction;

    // Current Character Reference
    UPROPERTY(BlueprintReadOnly, Category = "TWA_Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<ACharacterBase> CurrentCharacter;

public:

    virtual void SetupInputComponent() override;

private:
    // Input Bindings
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Jump();
    void StopJumping();
    void Run();
    void StopRunning();
};

void ACharacterControllerBase::Move(const FInputActionValue& Value)
{
}

void ACharacterControllerBase::Look(const FInputActionValue& Value)
{
}

void ACharacterControllerBase::Jump()
{
}

void ACharacterControllerBase::StopJumping()
{
}

void ACharacterControllerBase::Run()
{
}

void ACharacterControllerBase::StopRunning()
{
}
