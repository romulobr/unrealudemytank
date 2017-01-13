// Fill out your copyright notice in the Description page of Project Settings.

#include "battletank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *controlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	aimAtCrosshair();
}

void ATankPlayerController::aimAtCrosshair() const
{
	auto controlledTank = GetControlledTank();
	if (controlledTank)
	{
		OUT FVector hitLocation;
		if (gotSightRayHitLocationIn(hitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit location is: %s\n"), *hitLocation.ToString());
		}
	}
}

bool ATankPlayerController::gotAimingCoordinatesInto(FVector& worldLocation, FVector& lookDirection) const
{
	int32 OUT viewPortSizeX, OUT viewPortSizeY;
	GetViewportSize(OUT viewPortSizeX, OUT viewPortSizeY);
	FVector2D screenLocation = FVector2D(viewPortSizeX * crossHairXLocation, viewPortSizeY * crossHairYLocation);
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, lookDirection);
}

bool ATankPlayerController::hitSomethingAndPutResultsInto(OUT FHitResult& result, FVector* worldLocation, FVector* lookDirection) const
{
	auto start = *worldLocation;
	auto end = *worldLocation + (*lookDirection * aimRange);
	return GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility);
}

bool ATankPlayerController::gotSightRayHitLocationIn(OUT FVector& hitLocation) const
{
	bool hitSomething = false;
	hitLocation = FVector::ZeroVector;

	OUT FVector worldLocation;
	OUT FVector lookDirection;

	if (gotAimingCoordinatesInto(worldLocation, lookDirection))
	{
		OUT FHitResult result;
		if (hitSomethingAndPutResultsInto(result, &worldLocation, &lookDirection))
		{
			hitLocation = result.ImpactPoint;
			hitSomething = true;
		}
	}
	return hitSomething;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
