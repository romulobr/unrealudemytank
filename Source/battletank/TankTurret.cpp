

#include "battletank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	auto actualSpeed = FMath::Clamp(relativeSpeed, MinSpeed, MaxSpeed);
	auto rotateChange = actualSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawRotation = RelativeRotation.Yaw + rotateChange;
	auto newRotation = FMath::Clamp(rawRotation, MinRotationDegrees, MaxRotationDegrees);
	SetRelativeRotation(FRotator(0, newRotation, 0));
}
