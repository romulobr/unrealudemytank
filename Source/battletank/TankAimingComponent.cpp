// Fill out your copyright notice in the Description page of Project Settings.

#include "battletank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::moveBarrelTowards(FVector direction)
{
	OUT FHitResult result;
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = direction.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;
	barrel->Elevate(2.0f);
}

void UTankAimingComponent::AimAt(FVector targetLocation, float launchSpeed)
{
	auto name = GetOwner()->GetName();
	auto startLocation = barrel->GetSocketLocation(FName("projectile"));
	
	FVector OUT velocity;
	if(UGameplayStatics::SuggestProjectileVelocity(this, velocity, startLocation, targetLocation, launchSpeed, false))
	{
		auto aimDirection = velocity.GetSafeNormal();
		moveBarrelTowards(aimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s \n"), *name, *aimDirection.ToString());
	}		
}

void UTankAimingComponent::SetBarrel(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}
