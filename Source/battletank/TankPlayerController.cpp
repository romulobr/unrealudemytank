#include "battletank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

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
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	auto controlledTank = GetControlledTank();
	if (controlledTank)
	{
		OUT FVector hitLocation;
		if (gotSightRayHitLocationIn(hitLocation))
		{
			GetControlledTank()->AimAt(hitLocation);
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
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * 0.5, ViewportSizeY * 0.333);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, hitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * aimRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
