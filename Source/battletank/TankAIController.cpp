// Fill out your copyright notice in the Description page of Project Settings.

#include "battletank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	auto playerTank = GetPlayerTank();
	if(playerTank)
	{
		auto controlledTank = GetControlledTank();
		controlledTank->AimAt(playerTank->GetActorLocation());
		controlledTank->Fire();
	}
}