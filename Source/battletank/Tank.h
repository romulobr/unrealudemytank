#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UTankAimingComponent* aimingComponent;
public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void AimAt(FVector location);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* turret);
	
};
