// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay()"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Not in possession of a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In possession of tank: %s"), *(ControlledTank->GetName()) );
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	/*
	Because we need to access members of ATank, without the cast you wouldn't be able to call any of the functions of ATank.
	*/
	return Cast<ATank>(GetPawn());
}
