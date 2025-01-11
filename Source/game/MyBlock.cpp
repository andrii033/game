// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlock.h"

// Sets default values
AMyBlock::AMyBlock()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create a static mesh component
    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
    BlockMesh->SetSimulatePhysics(false); // Disable physics simulation
    BlockMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
    BlockMesh->SetMassOverrideInKg(NAME_None, 100.0f); // Increase mass to make the cubes more stable
    BlockMesh->SetLinearDamping(5.0f); // Increase linear damping to reduce movement
    BlockMesh->SetAngularDamping(5.0f); // Increase angular damping to reduce rotation
 
    RootComponent = BlockMesh;

    // Set the static mesh to SM_ChamferCube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMeshAsset(TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube"));
    if (BlockMeshAsset.Succeeded())
    {
        BlockMesh->SetStaticMesh(BlockMeshAsset.Object);
    }
    else
    {
      
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to find SM_ChamferCube mesh"));
    }

    // Set the initial scale of the block
    BlockMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
}


// Called when the game starts or when spawned
void AMyBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

