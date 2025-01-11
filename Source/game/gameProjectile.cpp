// Copyright Epic Games, Inc. All Rights Reserved.

#include "gameProjectile.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


AgameProjectile::AgameProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AgameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Set the MyBlock class directly
	MyBlock = AMyBlock::StaticClass();

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AgameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (MyBlock)
	{
		// Use the hit location to spawn the block
		FVector SpawnLocation = Hit.ImpactPoint;

		// Spawn the block
		for (int i = 0; i < 10; i++)
		{
			// Randomize the spawn location slightly by adding a random vector

			AMyBlock* SpawnedBlock = GetWorld()->SpawnActor<AMyBlock>(MyBlock, SpawnLocation, FRotator::ZeroRotator);
		}

		Destroy();
	}
}