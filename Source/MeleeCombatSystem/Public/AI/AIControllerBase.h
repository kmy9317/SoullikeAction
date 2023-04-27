// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRoation) const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "AICBsae")
	void DeterminAISightPerceptionViewPoint(FVector& OutLocation, FRotator& OutRoation) const;
};
