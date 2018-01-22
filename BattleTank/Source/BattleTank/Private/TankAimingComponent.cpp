// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine.h"
#include "GameFramework/Gamemode.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetComponentTickEnabled(true);

	//bWantsInitializeComponent = true;

	// ...
}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ensures that the tanks can't start firing as soon as the game starts
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::InitialiseAiming(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; } // 
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}


EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCount;
}

// As of UE4.18 in order for this tick component to tick I had to remove this TankAiming component from the Tank_BP blueprint and add it again.
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AimTowardsCrosshair();
	if (AmmoCount <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;

	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}

	// TODO handle aiming and locked states
}





bool UTankAimingComponent::IsBarrelMoving() const
{
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.1);


}




void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OurTankName = GetOwner()->GetName(); // GetOwner causes intellisense error if Engine.h is not included at the top of this file
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString() ;
	//UE_LOG(LogTemp, Warning, TEXT("Tank.cpp :- %s aiming at location : %s  : from barrel location %s "), *OurTankName, *HitLocation.ToString(), *BarrelLocation);


	// protect the Turret and Barrel 
	if (!ensure(Turret)) { return; }
	if (!ensure(Barrel)) { return; }

	// WorldContextObject will be the keyword 'this'

	// Toss Velocity
	FVector OutLaunchVelocity;

	// Start Location
	FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelFiringPoint"));

	
	/// The two lines below are for debug line traces
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Calculate the OutLaunchVelocity
	if (	UGameplayStatics::SuggestProjectileVelocity(
				this,
				OutLaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::DoNotTrace
				//,FCollisionResponseParams::DefaultResponseParam,
				//ActorsToIgnore,
				//true
				
			)
		)
	{

	
		// Aim direction
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);

		
	}
	else
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f No aim solution not found "), Time);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Turret && Barrel)) { return; }

	/// Work out the difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();



	// When the barrel is facing the same direction as the aim then the DeltaRotator calculated
	// in the next line will be zero.
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	if (DeltaRotator.Yaw > 180 || DeltaRotator.Yaw < -180)
	{
		DeltaRotator.Yaw = BarrelRotator.Yaw - AimAsRotator.Yaw ;
	}

	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator is  %s "), *DeltaRotator.ToString());

	/// The turret and barrel will be rotated at a set speed until DeltaRotator is zero
	//Turret->RotateTurret(DeltaRotator.GetNormalized().Yaw); // (Lecture 179)
	Turret->RotateTurret(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch); 
}






/**********  Code below  Originally in TankPlayerController.cpp    *******/



/// Start the tank moving the barrel so that a shot fired from the player's tank
/// will intersect the crosshair
void UTankAimingComponent::AimTowardsCrosshair()
{
	
	FVector OutHitLocation; // OUT parameter

	if (GetSightRayHitLocation(OutHitLocation)) //  Has side-effect, is going to line trace
	{
		AimAt(OutHitLocation);

	}

}




// Get world location if linetrace through crosshair dot
bool UTankAimingComponent::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
    GetWorld()->GetFirstPlayerController()->GetViewportSize(ViewportSizeX, ViewportSizeY);

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







bool UTankAimingComponent::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector PlayerWorldLocation; // not used anywhere but required for the DeprojectScreenPositionToWorld() function

	return GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, PlayerWorldLocation, LookDirection);

}



bool UTankAimingComponent::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult OutHitResult;

	auto StartLocation =  GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
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






/// Fire the main barrel weapon
void UTankAimingComponent::Fire()
{

	if (FiringStatus ==  EFiringStatus::Locked  || FiringStatus == EFiringStatus::Aiming) {

		
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
	/// Spawn a projectile at firing socket location and then call the LaunchProjectile method of the returned 
	///  Projectile class 
		auto LaunchedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelFiringPoint")),
			Barrel->GetSocketRotation(FName("BarrelFiringPoint")) // ensure the projectile has the same rotation as the barrel
			);

		LaunchedProjectile->LaunchProjectile(LaunchSpeed);

		
		LastFireTime = FPlatformTime::Seconds();
		AmmoCount -= 1;
		
	}
}

