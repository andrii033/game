#include "MyBlock.h"
#include "TimerManager.h"

// Sets default values
AMyBlock::AMyBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetSimulatePhysics(true); // Enable physics simulation
	BlockMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	BlockMesh->SetMassOverrideInKg(NAME_None, 1000.0f); // Increase mass to make the cubes more stable
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

	// Initialize scaling variables
	ScalingSpeed = 1.5f; // Scale per second
	TargetScale = FVector(0.5f, 0.5f, 0.5f); // Target scale
}

// Called when the game starts or when spawned
void AMyBlock::BeginPlay()
{
	Super::BeginPlay();

	// Set a timer to disable physics after 2 seconds
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyBlock::DisablePhysics, 1.0f, false);
}

// Called every frame
void AMyBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Gradually increase the scale of the block
	FVector CurrentScale = BlockMesh->GetComponentScale();
	FVector NewScale = FMath::VInterpTo(CurrentScale, TargetScale, DeltaTime, ScalingSpeed);
	BlockMesh->SetWorldScale3D(NewScale);
}

// Function to disable physics
void AMyBlock::DisablePhysics()
{
	BlockMesh->SetSimulatePhysics(false);
}


