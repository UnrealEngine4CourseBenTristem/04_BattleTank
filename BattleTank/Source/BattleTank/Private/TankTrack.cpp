// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"





// Sets a throttle between -1 and +1
void UTankTrack::SetThrottle(float Throttle) 
{

	// TODO Clamp Throttle value so that player can't over-drive


	//auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle - %f"), *Name, Throttle);


}