// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



float UTankTrack::GetTrackMaxDrivingForce()
{
	return TrackMaxDrivingForce;
}

// Sets a throttle between -1 and +1
void UTankTrack::SetThrottle(float Throttle) 
{

	// TODO Clamp Throttle value so that player can't over-drive


	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s Throttle - %f"), *Name, Throttle);

	// Calculate the force that will be applied
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;


	// Get the location where the force will be applied to
	auto ForceLocation = GetComponentLocation();

	// Get the thing that the force will be applied to.
	// The most basic object type that we can apply a force to is the
	// UPrimitveComponent so the GetRootComponent returns a USceneComponent 
	// Therefore a cast to UPrimitiveComponent is required
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}