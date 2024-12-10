// Fill out your copyright notice in the Description page of Project Settings.


#include "TutBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TutAttributeComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"




// Sets default values
ATutBaseProjectile::ATutBaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATutBaseProjectile::OnActorOverlap);

	RootComponent = SphereComp;

	ProjectileEffectComponent = CreateDefaultSubobject<UNiagaraComponent>("ProjectileEffectComponent");
	ProjectileEffectComponent->SetupAttachment(SphereComp);


	MovementComp = CreateDefaultSubobject <UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	ProjectileLoop = CreateDefaultSubobject<UAudioComponent>("ProjectileAudio");
	ProjectileLoop->SetupAttachment(SphereComp);

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ATutBaseProjectile::CalculateProjectileDirection()
{

	FVector CameraLocation;
	FRotator CameraRotation;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not Found!"));
		return;
	}

	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector RayEnd = CameraLocation + (CameraRotation.Vector() * MaxRayCastDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, RayEnd, ECC_Visibility, QueryParams);

	FVector TargetLocation;
	if (bHit)
	{
		TargetLocation = HitResult.ImpactPoint;
	}
	else
	{
		TargetLocation = RayEnd;
	}

	DrawDebugLine(GetWorld(), CameraLocation, TargetLocation, FColor::Green, false, 2.f);

	FVector Direction = TargetLocation - GetActorLocation();
	Direction.Normalize();

	if (MovementComp)
	{
		MovementComp->Velocity = Direction * MovementComp->InitialSpeed;
	}

	FRotator NewRotation = Direction.Rotation();

	SetActorRotation(NewRotation);

}

void ATutBaseProjectile::CallExplosion()
{	
	if (!GetWorld())
	{		
		return;
	}
	if (ImpactEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f));
	}
	if (ProjectileImpact)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProjectileImpact, GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Explosion Effect Is Not Set"));
	}


	if (!PlayerCharacter)
	{
		return;
	}

	float Distance = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());

	float MaxShakeDistance = 1000.0f; // Maximum distance for the shake
	float MinShakeDistance = 200.0f;  // Minimum distance for maximum shake intensity

	if (Distance <= MaxShakeDistance)
	{
		// Calculate shake intensity based on distance
		float ShakeScale = 1.0f - FMath::Clamp((Distance - MinShakeDistance) / (MaxShakeDistance - MinShakeDistance), 0.0f, 1.0f);

		// Apply camera shake
		APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
		if (PlayerController && CameraShakeClass)
		{
			PlayerController->ClientStartCameraShake(CameraShakeClass, ShakeScale);
			UE_LOG(LogTemp, Warning, TEXT("Playing camera shake is not set!"));
		}
		else if (!CameraShakeClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("CameraShakeClass is not set!"));
		}
	}
}



// Called when the game starts or when spawned
void ATutBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	CalculateProjectileDirection();

	if (ProjectileLoop)
	{
		ProjectileLoop->Play();
	}
	
}

// Called every frame
void ATutBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutBaseProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		UTutAttributeComponent* AttributeComp = Cast<UTutAttributeComponent>(OtherActor->GetComponentByClass(UTutAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.f);

			Destroy();

			UE_LOG(LogTemp, Warning, TEXT("POJECTILE DESTROYED"));
		}
	}
}