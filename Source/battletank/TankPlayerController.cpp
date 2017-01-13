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
	auto end = *worldLocation + (*lookDirection * 100000.0f);
	DrawDebugLine(GetWorld(), start, end, FColor(255, 255, 100), false, 0.0f, 0.0f, 3.0f);
	UE_LOG(LogTemp, Warning, TEXT("\n\n\nstart: %s end %s\n\n\n"), *start.ToString(), *end.ToString());
	return GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility);
}

bool ATankPlayerController::gotSightRayHitLocationIn(OUT FVector& hitLocation) const
{
	OUT FVector worldLocation;
	OUT FVector lookDirection;

	if (gotAimingCoordinatesInto(worldLocation, lookDirection))
	{
		OUT FHitResult result;
		if (hitSomethingAndPutResultsInto(result, &worldLocation, &lookDirection))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s\n"), *result.ToString());
			hitLocation = result.ImpactPoint;
			return true;
		};
	}
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
