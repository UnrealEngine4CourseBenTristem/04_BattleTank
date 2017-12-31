// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Engine.h"
#include "Projectile.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added in the constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>("Aiming Component");

}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);

	// Local barrel
	Barrel = BarrelToSet;
	
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}



// Aim at passed FVector
void ATank::AimAt( FVector HitLocation)
{
	
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);

}


/// Fire the main barrel weapon
void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && bIsReloaded) {

		

		/// Spawn a projectile at firing socket location and then call the LaunchProjectile method of the returned 
		///  Projectile class 
		auto LaunchedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelFiringPoint")),
			Barrel->GetSocketRotation(FName("BarrelFiringPoint")) // ensure the projectile has the same rotation as the barrel
			);

		LaunchedProjectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}