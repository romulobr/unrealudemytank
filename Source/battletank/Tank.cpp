// Fill out your copyright notice in the Description page of Project Settings.

#include "battletank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	aimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponentToSet)
{
	Super::SetupPlayerInputComponent(InputComponentToSet);
}

void ATank::AimAt(FVector location)
{
	aimingComponent->AimAt(location, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
	aimingComponent->SetBarrel(barrelToSet);
}

void ATank::SetTurret(UTankTurret* turret)
{
	aimingComponent->SetTurret(turret);
}

void ATank::Fire()
{
	auto readyToFire = barrel && ((FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds);
	if (readyToFire)
	{
		auto location = barrel->GetSocketLocation(PROJECTILE_NAME);
		auto rotation = barrel->GetSocketRotation(PROJECTILE_NAME);
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, location, rotation);
		projectile->LaunchProjectile(LaunchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}
