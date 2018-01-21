// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Delegate.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetComponentTickEnabled(true);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();


	// Register Delegate
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);


}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();

	// Apply sideways force
	ApplySidewaysForce();

	CurrentThrottle = 0;
}




void UTankTrack::ApplySidewaysForce()
{
	// Work out required acceleration this frame
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// In order to get the mass of the tank we need the tank root 
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// 	Calculate sideways friction(Force = mass * acceleration)
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;

	// Finally apply the force to the tank
	TankRoot->AddForce(CorrectionForce);
}



float UTankTrack::GetTrackMaxDrivingForce()
{
	return TrackMaxDrivingForce;
}



// Sets a throttle between -1 and +1
void UTankTrack::SetThrottle(float Throttle) 
{

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s Throttle - %f"), *Name, Throttle);

	// Calculate the force that will be applied
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;


	// Get the location where the force will be applied to
	auto ForceLocation = GetComponentLocation();

	// Get the thing that the force will be applied to.
	// The most basic object type that we can apply a force to is the
	// UPrimitveComponent so the GetRootComponent returns a USceneComponent 
	// Therefore a cast to UPrimitiveComponent is required
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
