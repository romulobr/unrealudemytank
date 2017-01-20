#include "battletank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	auto actualSpeed = FMath::Clamp(relativeSpeed, MinSpeed, MaxSpeed);
	auto elevationChange = actualSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto newElevation = FMath::Clamp(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(newElevation, 0, 0));
}
