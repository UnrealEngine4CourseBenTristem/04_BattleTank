// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	

private:
	// Max Force per Track In Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; // Assume tank is 40,000Kg and acceleration is 10m/s per second, i.e. 1g
public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);


	float GetTrackMaxDrivingForce();


};
