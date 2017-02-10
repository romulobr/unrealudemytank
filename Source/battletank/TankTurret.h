

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float relativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 20;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxRotationDegrees = 180;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinRotationDegrees = -180;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinSpeed = -1;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxSpeed = 1;
};
