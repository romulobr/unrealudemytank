// Fill out your copyright notice in the Description page of Project Settings.

#include "battletank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	
	if(controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *controlledTank->GetName());
	}	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Player controller ticked"));
}

void ATankPlayerController::aimAtCrosshair()
{
	auto controlledTank = GetControlledTank();
	if(!controlledTank)
	{
		
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
