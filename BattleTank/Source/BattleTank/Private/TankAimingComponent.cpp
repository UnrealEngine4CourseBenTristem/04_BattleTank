// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine.h"
#include "GameFramework/Gamemode.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

//void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
//{
//	if (!BarrelToSet) { return;  }
//	Barrel = BarrelToSet;
//
//}
//
//void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
//{	
//	if (!TurretToSet) { return; }
//	Turret = TurretToSet;
//}

void UTankAimingComponent::InitialiseAiming(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OurTankName = GetOwner()->GetName(); // GetOwner causes intellisense error if Engine.h is not included at the top of this file
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString() ;
	//UE_LOG(LogTemp, Warning, TEXT("Tank.cpp :- %s aiming at location : %s  : from barrel location %s "), *OurTankName, *HitLocation.ToString(), *BarrelLocation);


	// protect the Turret and Barrel 
	if (!Turret) { return; }
	if (!Barrel) { return; }

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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

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
	if (!Turret || !Barrel) { return; }

	/// Work out the difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	// When the barrel is facing the same direction as the aim then the DeltaRotator calculated
	// in the next line will be zero.
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	

	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator is  %s "), *DeltaRotator.ToString());

	/// The turret and barrel will be rotated at a set speed until DeltaRotator is zero
	//Turret->RotateTurret(DeltaRotator.GetNormalized().Yaw); // (Lecture 179)
	Turret->RotateTurret(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch); 
}
