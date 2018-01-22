// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


// Forward declaration
class UTankBarrel; // Holds barrel's properties and elevation method
class UTankTurret; // Holds turret's properties and yaw rotation method 
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	// How far ahead of the player can we reach in cm
	float LineTraceRange = 100000.0;

	// ***********  Originally in TankPlayerController.h ***********************************


	void AimTowardsCrosshair();

	// 
	FVector AimDirection;

	// Return an OUT parameter, True if hit landscape
	bool GetSightRayHitLocation(FVector & OutHitLocation) const;

	// Put into LookDirection parameter the direction in which the TankPlayerController is looking
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	// return the result of a line trace
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	// check if barrel is moving
	bool IsBarrelMoving() const;


	// Screen crosshair location multiplier to get the X and Y positions as a percentage of the screen size
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f; // half-way across the screen
	float CrosshairYLocation = 0.33333f;


	// *************************************************************************************




	/****************** Originally from Tank.h ****************/
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; // TODO: find sensible starting value default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;  	// info https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int AmmoCount = 5;

	// Reload time in seconds
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	/********************************************************/




protected:
	// Needs to be in the protected area because FiringStatus needs to be accessed by this class's sub class which
	// is the TankPlayerController_BP which has a reference to ATank class
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseAiming(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);
	
	// Called every frame
	virtual void TickComponent
	(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction * ThisTickFunction
	) override;


	EFiringStatus GetFiringState() const; // const because we don't want it changing any member variables
	

	// Fire the main barrel
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();


	UFUNCTION(BlueprintCallable, Category = "Setup")
		int GetAmmoCount() const;
};
