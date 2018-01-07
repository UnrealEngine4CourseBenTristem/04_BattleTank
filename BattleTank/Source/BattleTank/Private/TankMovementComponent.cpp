// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


// This function is called automatically by the AI movement logic once the call to ToMoveActor() in TankAIController.cpp Tick() has been made
// 
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we are replacing completely

	// Get current direction that the tank is facing
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Get unit vector of direction that AI tank wants to travel
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();


	// UE_LOG(LogTemp, Warning, TEXT("%s Move vector  %s"), *GetOwner()->GetName(), *AIForwardIntention.ToString());


	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	
	IntendMoveForward(ForwardThrow);

	IntendTurn(TurnThrow);
	

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{

	//UE_LOG(LogTemp, Warning, TEXT("Intend move  %f"), Throw);
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
	
	//UE_LOG(LogTemp, Warning, TEXT("%s Move vector  %f "), *GetOwner()->GetName(), Throw);


	// TODO: Prevent this function from working if the shoulder buttons are depresesed to avoid double speed

}



void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}



