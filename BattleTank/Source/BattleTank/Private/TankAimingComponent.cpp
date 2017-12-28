// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Engine.h"
#include "GameFramework/Gamemode.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{

	Barrel = BarrelToSet;

}




void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OurTankName = GetOwner()->GetName(); // GetOwner causes intellisense error if Engine.h is not included at the top of this file
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString() ;
	//UE_LOG(LogTemp, Warning, TEXT("Tank.cpp :- %s aiming at location : %s  : from barrel location %s "), *OurTankName, *HitLocation.ToString(), *BarrelLocation);


	// protect the Barrel 
	if (!Barrel) { return; }

	// WorldContextObject will be the keyword 'this'

	// Toss Velocity
	FVector OutLaunchVelocity;

	// Start Location
	FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelFiringPoint"));

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

			)
		)
	{

	
		// Aim direction
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);

		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at  %s "), *OurTankName, *AimDirection.ToString());

	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/// Work out the difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator is  %s "), *DeltaRotator.ToString());


	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
}