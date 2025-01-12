// Copyright Epic Games, Inc. All Rights Reserved.

#include "gameProjectile.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "gameCharacter.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>


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
    AgameCharacter* PlayerCharachter = Cast<AgameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    switch (PlayerCharachter->ShotMode)
    {
    case 0:
        CreatedBlock(Hit);
        break;
    case 1:
        DestroyedBlock(Hit);
        break;
    default:
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("non-existent shot mode: %s"), PlayerCharachter->ShotMode));
        break;
    }
    Destroy();
}

void AgameProjectile::CreatedBlock(const FHitResult& Hit)
{
    if (MyBlock)
    {
        // Use the hit location to spawn the block
        FVector SpawnLocation = Hit.ImpactPoint;

        // Define the block size (assuming 100 units in each dimension)
        const float BlockSize = 50.0f;

        // Adjust the spawn location to ensure the blocks touch at the sides
        FVector AdjustedSpawnLocation = SpawnLocation + Hit.Normal * BlockSize;

        // Round each component to the nearest multiple of 100
        AdjustedSpawnLocation.X = FMath::RoundToInt(AdjustedSpawnLocation.X / BlockSize) * BlockSize;
        AdjustedSpawnLocation.Y = FMath::RoundToInt(AdjustedSpawnLocation.Y / BlockSize) * BlockSize;
        AdjustedSpawnLocation.Z = FMath::RoundToInt(AdjustedSpawnLocation.Z / BlockSize) * BlockSize;

        // Spawn the block
        for (int i = 0; i < 1; i++)
        {
            AMyBlock* SpawnedBlock = GetWorld()->SpawnActor<AMyBlock>(MyBlock, AdjustedSpawnLocation, FRotator::ZeroRotator);
            if (SpawnedBlock)
            {
                SpawnedBlock->Tags.Add("MyBlock");
                // Optionally, add debug message
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Block Spawned at: %s"), *SpawnedBlock->GetActorLocation().ToString()));
            }

            // Update the spawn location for the next block
            AdjustedSpawnLocation += Hit.Normal * BlockSize;

            // Round each component to the nearest multiple of 100 again
            AdjustedSpawnLocation.X = FMath::RoundToInt(AdjustedSpawnLocation.X / BlockSize) * BlockSize;
            AdjustedSpawnLocation.Y = FMath::RoundToInt(AdjustedSpawnLocation.Y / BlockSize) * BlockSize;
            AdjustedSpawnLocation.Z = FMath::RoundToInt(AdjustedSpawnLocation.Z / BlockSize) * BlockSize;
        }
    }
}

void AgameProjectile::DestroyedBlock(const FHitResult& Hit)
{
    if (Hit.GetActor()->Tags.FindByKey("MyBlock"))
    {
        Hit.GetActor()->Destroy();
    }
}


