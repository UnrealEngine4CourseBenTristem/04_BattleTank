// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"





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

	
	FVector OutHitLocation;

	if (GetSightRayHitLocation(OutHitLocation)) //  Has side-effect, is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction is : %s "), *(OutHitLocation.ToString()));
		
		  // TODO: Tell player controlled tank to aim at this point 

		//UE_LOG(LogTemp, Warning, TEXT("Tick tock"));

	}
	else
	{
	
		
	}
	

	

}

// Get world location if linetrace through crosshair dot
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector PlayerLookDirection;

	/// De-project the screen co-ordinate to a world co-ordinate look direction
	if (GetLookDirection(ScreenLocation, PlayerLookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerLookDirection direction is X : %s "), *PlayerLookDirection.ToString());
	}
	

	// Line-trace along that look direction, and see what we hit (up to max range)

	OutHitLocation = FVector(1.0);
	
	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	
	FVector PlayerWorldLocation; // not used anywhere but required for the DeprojectScreenPositionToWorld() function

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, PlayerWorldLocation, LookDirection);
	
}