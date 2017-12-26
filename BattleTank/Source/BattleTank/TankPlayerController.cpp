// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankPlayerController.h"






void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay()"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player not in possession of a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player in possession of tank: %s"), *(ControlledTank->GetName()) );
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	/*
	Because we need to access members of ATank, without the cast you wouldn't be able to call any of the functions of ATank.
	*/
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
}

/// Start the tank moving the barrel so that a shot fired from the player's tank
/// will intersect the crosshair
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	

	// Get world location if linetrace through crosshair dot
	// if it hits the landscape 
		// tell player controlled tank to aim at this point 

	UE_LOG(LogTemp, Warning, TEXT("Tick tock"));

	

}

