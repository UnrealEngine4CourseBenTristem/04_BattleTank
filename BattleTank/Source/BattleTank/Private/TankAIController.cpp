// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(PlayerTank))
	{

		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		/// Aim towards player
		Cast<ATank>(GetPawn())->AimAt(Cast<ATank>(PlayerTank)->GetActorLocation());

		//Fire
		Cast<ATank>(GetPawn())->Fire();
	}
}


