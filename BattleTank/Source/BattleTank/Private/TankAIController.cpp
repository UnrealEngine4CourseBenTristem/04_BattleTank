// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerControlledTank = GetPlayerControlledTank();


	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI not in possession of a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI in possession of tank: %s"), *(ControlledTank->GetName()));
	}


	if (!PlayerControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI couldn't find player controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player controller: %s"), *(PlayerControlledTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerControlledTank())
	{
		// TODO: Move towards player

		/// Aim towards player
		GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());

		//Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	/*
	Because we need to access members of ATank, without the cast you wouldn't be able to call any of the functions of ATank.
	*/
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerControlledTank() const
{
	/*
	Because we need to access members of ATank, without the cast you wouldn't be able to call any of the functions of ATank.
	*/

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
	
}