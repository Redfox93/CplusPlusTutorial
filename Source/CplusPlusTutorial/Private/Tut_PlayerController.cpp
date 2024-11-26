#include "Tut_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ATut_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Add Input Mapping Context to the Enhanced Input Local Player Subsystem
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
        {
            if (IMC_Default)
            {
                Subsystem->AddMappingContext(IMC_Default, 0);
                UE_LOG(LogTemp, Warning, TEXT("Input Mapping Context successfully added."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("IMC_Default is null! Please assign a valid InputMappingContext in the Blueprint."));
            }
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
