// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last #include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank * GetControlledTank() const;

	// Aim towards cross hair
	void AimTowardsCrosshair();

	// Return an OUT parameter, True if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// How far ahead of the player can we reach in cm
	float Reach = 10000.0;

	// Screen crosshair location multiplier to get the X and Y positions as a percentage of the screen size
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f; // half-way across the screen
		float CrosshairYLocation = 0.33333f;

public:
	

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
