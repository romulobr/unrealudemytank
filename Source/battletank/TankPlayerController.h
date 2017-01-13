// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	const FCollisionQueryParams colisionQueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	const FCollisionObjectQueryParams objectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_Visibility);

	void aimAtCrosshair() const;
	bool gotAimingCoordinatesInto(FVector& worldLocation, FVector& lookDirection) const;
	bool hitSomethingAndPutResultsInto(FHitResult& result, FVector* worldLocation, FVector* lookDirection) const;

	bool gotSightRayHitLocationIn(OUT FVector& hitLocation) const;

public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaTime);

	UPROPERTY(EditAnywhere)
	float crossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float crossHairYLocation = 0.33333;
};
