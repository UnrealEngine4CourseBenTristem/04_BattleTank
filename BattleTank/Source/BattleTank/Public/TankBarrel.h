// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )//, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 5; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevation  = 30; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevation = 0; 

public:
	// -1 is max downwards speed and +1 is max upwards speed
	void Elevate(float RelativeSpeed);
	
	
};
