// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"





void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		 //Call this function that is defined in header file
		 //There is no need to implement the function in this .cpp file
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




