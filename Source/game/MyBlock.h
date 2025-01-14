// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBlock.generated.h"

UCLASS()
class GAME_API AMyBlock : public AActor
{
	GENERATED_BODY()
private:
	void DisablePhysics();
	// Add this line to declare TimerHandle
	FTimerHandle TimerHandle;
	
public:	
	// Sets default values for this actor's properties
	AMyBlock();

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
