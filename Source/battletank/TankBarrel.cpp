#include "battletank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	auto elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;

	SetRelativeRotation(FRotator(rawNewElevation, 0, 0));	
}
