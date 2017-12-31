// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000.0f; // TODO: find sensible starting value default

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;  	// info https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	// Reload time in seconds
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// aiming component
	UTankAimingComponent* TankAimingComponent = nullptr;

	

public:	
	// Sets default values for this pawn's properties
	ATank();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void AimAt(FVector HitLocation);

	// Barrel reference able to be called from blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Barrel reference able to be called from blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	// Fire the main barrel
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();
	
};
