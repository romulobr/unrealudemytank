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

	// ...
}

void UTankAimingComponent::AimAt(FVector location)
{
	auto name = GetOwner()->GetName();
	FVector barrelLocation;
	if (barrel)
	{
		barrelLocation = barrel->GetComponentLocation();
	}
	else
	{
		barrelLocation = FVector::ZeroVector;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s, from: %s\n"), *name, *location.ToString(), *barrelLocation.ToString());
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* barrelToSet)
{
	barrel = barrelToSet;
}
