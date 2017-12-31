// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn)
	{

		// TODO: Move towards player

		/// Aim towards player
		Cast<ATank>(GetPawn())->AimAt(Cast<ATank>(PlayerPawn)->GetActorLocation());

		//Fire
		Cast<ATank>(GetPawn())->Fire();
	}
}


