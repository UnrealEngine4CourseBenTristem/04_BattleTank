// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"





void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay()"));

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at BeginPlay()"));
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
	if (!ensure(GetControlledTank())) { return; }

	
	FVector OutHitLocation; // OUT parameter

	if (GetSightRayHitLocation(OutHitLocation)) //  Has side-effect, is going to line trace
	{
		GetControlledTank()->AimAt( OutHitLocation);
		

	}

}



// Get world location if linetrace through crosshair dot
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	/// De-project the screen co-ordinate to a world co-ordinate look direction
	FVector PlayerLookDirection;
	if (GetLookDirection(ScreenLocation, PlayerLookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(PlayerLookDirection, OutHitLocation);
		
	}
	
	return false;
	
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	
	FVector PlayerWorldLocation; // not used anywhere but required for the DeprojectScreenPositionToWorld() function

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, PlayerWorldLocation, LookDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation ) const
{
	FHitResult OutHitResult;
	
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)

		) 
	{ 
		HitLocation = OutHitResult.Location;
		return true;
	}
	HitLocation = FVector(0); // Set hit location to zero if nothing hit
	return false; // Line-trace didn't succeed
}
