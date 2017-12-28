// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBarrel.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000.0f; // TODO: find sensible starting value default

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt( FVector HitLocation);

	// Barrel reference able to be called from blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// aiming component
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	
};
