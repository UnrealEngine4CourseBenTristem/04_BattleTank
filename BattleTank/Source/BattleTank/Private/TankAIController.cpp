// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(PlayerTank))
	{

		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		/// Aim towards player
		// TODO: Get this to work. AimAt is now in TankAimingComponent
		Cast<UTankAimingComponent>(Cast<ATank>(GetPawn())->GetComponentByClass(UTankAimingComponent::StaticClass()))->AICalledAimAt(Cast<ATank>(PlayerTank)->GetActorLocation());
		
		//Cast<ATank>(GetPawn())->AimAt(Cast<ATank>(PlayerTank)->GetActorLocation());



		//Fire
		//Cast<ATank>(GetPawn())->Fire();
		Cast<UTankAimingComponent>(Cast<ATank>(GetPawn())->GetComponentByClass(UTankAimingComponent::StaticClass()))->Fire();
	}
}


