// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBlock.generated.h"

UCLASS()
class GAME_API AMyBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static mesh component for the block
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BlockMesh;

	// Variables for scaling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scaling")
	float ScalingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scaling")
	FVector TargetScale;
};
