// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	
	SetRootComponent(CollisionMesh);
	
	CollisionMesh->SetNotifyRigidBodyCollision(true); // Simulation Generates Hit Events is now defaulting to true
	CollisionMesh->SetVisibility(false);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachTo(RootComponent);

	// Make sure it doesn't start off moving until it's fired
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::LaunchProjectile(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f LaunchProjectile with speed %f"), Time, Speed);

	// Set velocity and direction of the projectile
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); // The forward vector of the projectile was set when we spawned the projectile 
																					// in ATank::Fire()

	// Launch it 
	ProjectileMovement->Activate();

}
