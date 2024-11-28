#include "Tut_Character.h"
#include "Tut_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h"
#include "TutInteractionComponent.h"

// Sets default values
ATut_Character::ATut_Character()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up the SpringArm component
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->SetupAttachment(RootComponent);

    // Create and set up the Camera component
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComp->SetupAttachment(SpringArmComp);
    CameraComp->bUsePawnControlRotation = false;

    //IMPLEMENT BINDING! LIKE "F" FOR INTERACT
    InteractionComp = CreateDefaultSubobject<UTutInteractionComponent>(TEXT("InteractionComponent"));

    // Character Movement Configuration
    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    if (MovementComponent)
    {
        MovementComponent->bOrientRotationToMovement = true; // Character faces in the direction of movement
        MovementComponent->RotationRate = FRotator(0.f, 540.f, 0.f);
    }

    // Disable controller rotation for the character
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ATut_Character::BeginPlay()
{
    Super::BeginPlay();

    ATut_PlayerController* MyPlayerController = Cast<ATut_PlayerController>(GetController());
    if (MyPlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller successfully accessed from Character."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to access Player Controller from Character."));
    }
}

// Called every frame
void ATut_Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Draw Debug Arrows to visualize direction
    if (Controller)
    {
        // Character's Forward Direction
        FVector CharacterLocation = GetActorLocation();
        FVector CharacterForward = GetActorForwardVector();
        FVector CharacterRight = GetActorRightVector();
        DrawDebugDirectionalArrow(GetWorld(), CharacterLocation + CharacterRight * 100.0f,
            CharacterLocation + CharacterForward * 200.0f + CharacterRight * 100.0f,
            100.0f, FColor::Green, false, -1.0f, 0, 5.0f);

        // Controller's Forward Direction
        FVector ControllerForward = FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X);
        DrawDebugDirectionalArrow(GetWorld(), CharacterLocation + CharacterRight * 100.0f,
            CharacterLocation + ControllerForward * 200.0f + CharacterRight * 100.0f,
            100.0f, FColor::Blue, false, -1.0f, 0, 5.0f);
    }
}

// Called to bind functionality to input
void ATut_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        ATut_PlayerController* MyPlayerController = Cast<ATut_PlayerController>(GetController());
        if (MyPlayerController)
        {
            if (MyPlayerController->IA_Move)
            {
                EnhancedInputComponent->BindAction(MyPlayerController->IA_Move, ETriggerEvent::Triggered, this, &ATut_Character::Move);
            }
            if (MyPlayerController->IA_Look)
            {
                EnhancedInputComponent->BindAction(MyPlayerController->IA_Look, ETriggerEvent::Triggered, this, &ATut_Character::Look);
            }
            if (MyPlayerController->IA_Jump)
            {
                EnhancedInputComponent->BindAction(MyPlayerController->IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
            }
            if (MyPlayerController->IA_Run)
            {
                EnhancedInputComponent->BindAction(MyPlayerController->IA_Run, ETriggerEvent::Started, this, &ATut_Character::Run);
                EnhancedInputComponent->BindAction(MyPlayerController->IA_Run, ETriggerEvent::Completed, this, &ATut_Character::StopRun);
            }
            if (MyPlayerController->IA_PrimaryAttack)
            {
                EnhancedInputComponent->BindAction(MyPlayerController->IA_PrimaryAttack, ETriggerEvent::Triggered, this, &ATut_Character::PrimaryAttack);
            }
            if (MyPlayerController->IA_PrimaryInteract)
            {
                EnhancedInputComponent->BindAction(MyPlayerController->IA_PrimaryInteract, ETriggerEvent::Triggered, this, &ATut_Character::PrimaryInteract);
            }
        }
    }
}

void ATut_Character::Move(const FInputActionValue& Value)
{
    FVector2D MoveValue = Value.Get<FVector2D>();
    if (Controller != nullptr)
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FVector ForwardDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MoveValue.Y);
        AddMovementInput(RightDirection, MoveValue.X);
    }
}

void ATut_Character::Look(const FInputActionValue& Value)
{
    FVector2D LookValue = Value.Get<FVector2D>();
    if (Controller != nullptr)
    {
        AddControllerYawInput(LookValue.X);
        AddControllerPitchInput(LookValue.Y);
    }
}

void ATut_Character::Run(const FInputActionValue& Value)
{
    if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
    {
        float OldSpeed = MovementComponent->MaxWalkSpeed;
        MovementComponent->MaxWalkSpeed *= 2.0f;
        UE_LOG(LogTemp, Warning, TEXT("Running: Old Speed = %f, New Speed = %f"), OldSpeed, MovementComponent->MaxWalkSpeed);
    }
}

void ATut_Character::StopRun(const FInputActionValue& Value)
{
    if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
    {
        float OldSpeed = MovementComponent->MaxWalkSpeed;
        MovementComponent->MaxWalkSpeed /= 2.0f;
        UE_LOG(LogTemp, Warning, TEXT("Stopped Running: Old Speed = %f, New Speed = %f"), OldSpeed, MovementComponent->MaxWalkSpeed);
    }
}

void ATut_Character::PrimaryAttack()
{

    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ATut_Character::PrimaryAttack_TimeElapsed, 0.35f);
  //  GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);

}

void ATut_Character::PrimaryAttack_TimeElapsed()
{

    USkeletalMeshComponent* MyMesh = GetMesh();



    FVector SpawnLocation;
    FRotator SpawnRotation;
    MyMesh->GetSocketWorldLocationAndRotation("hand_l_Socket",SpawnLocation,SpawnRotation);
    FTransform SpawnTM = FTransform(GetControlRotation(), SpawnLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

    DrawDebugSphere(GetWorld(), SpawnLocation, 10.f, 12, FColor::Red, false, 5.0f, 0, 2.0f);


}

void ATut_Character::PrimaryInteract()
{
    if (InteractionComp)
    {
        InteractionComp->PrimaryInteract();
    }
   
}
