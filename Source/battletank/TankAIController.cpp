// Fill out your copyright notice in the Description page of Project Settings.

#include "battletank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	auto playerTank = GetPlayerTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank: %s"), *controlledTank->GetName());
	}
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Found"), *controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could NOT find player tank"), *controlledTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* playerTankOrNull = nullptr;
	if (playerPawn)
	{
		playerTankOrNull = Cast<ATank>(playerPawn);
	}
	return playerTankOrNull;
}
