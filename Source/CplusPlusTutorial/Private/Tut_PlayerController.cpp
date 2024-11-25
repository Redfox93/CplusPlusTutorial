#include "Tut_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tut_Character.h"

void ATut_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Ensure the InputComponent is an EnhancedInputComponent
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Bind each of your input actions
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATut_PlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ATut_PlayerController::Look);
        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ATut_PlayerController::Jump);
        EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Started, this, &ATut_PlayerController::Run);
        EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed, this, &ATut_PlayerController::StopRun);
    }
}

void ATut_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Access the local player and add the input mapping context
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
        {
            Subsystem->AddMappingContext(IMC_Default, 0);
            UE_LOG(LogTemp, Warning, TEXT("Input Mapping Context successfully added."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get EnhancedInputLocalPlayerSubsystem!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get LocalPlayer!"));
    }
}

void ATut_PlayerController::Move(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        FVector2D MoveValue = Value.Get<FVector2D>();
        // Use the character's rotation for movement rather than the control rotation
        FVector Forward = ControlledPawn->GetActorForwardVector();
        FVector Right = ControlledPawn->GetActorRightVector();

        ControlledPawn->AddMovementInput(Forward, MoveValue.Y);
        ControlledPawn->AddMovementInput(Right, MoveValue.X);
    }
}


void ATut_PlayerController::Look(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        FVector2D LookValue = Value.Get<FVector2D>();
        AddYawInput(LookValue.X);
        AddPitchInput(LookValue.Y);
    }
}

void ATut_PlayerController::Jump(const FInputActionValue& Value)
{
    if (ATut_Character* ControlledCharacter = Cast<ATut_Character>(GetPawn()))
    {
        ControlledCharacter->Jump();
    }
}

void ATut_PlayerController::Run(const FInputActionValue& Value)
{
    if (ATut_Character* ControlledCharacter = Cast<ATut_Character>(GetPawn()))
    {
        float OldSpeed = ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed;
        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed *= 2.0f; // Example multiplier for running speed
        UE_LOG(LogTemp, Warning, TEXT("Running: Old Speed = %f, New Speed = %f"), OldSpeed, ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed);
    }
}

void ATut_PlayerController::StopRun(const FInputActionValue& Value)
{
    if (ATut_Character* ControlledCharacter = Cast<ATut_Character>(GetPawn()))
    {
        float OldSpeed = ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed;
        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed /= 2.0f; // Resetting the speed back to normal
        UE_LOG(LogTemp, Warning, TEXT("Stopped Running: Old Speed = %f, New Speed = %f"), OldSpeed, ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed);
    }
}
