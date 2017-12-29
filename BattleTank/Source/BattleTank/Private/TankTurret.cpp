// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine.h"

void UTankTurret::RotateTurret(float TurretRelativeSpeed)
{

	TurretRelativeSpeed = FMath::Clamp<float>(TurretRelativeSpeed, -1, 1);

	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f turret-> called with speed of  %f "), Time, TurretRelativeSpeed);

	auto RotationChange = TurretRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	

	SetRelativeRotation(FRotator(0, NewRotation, 0));


}
