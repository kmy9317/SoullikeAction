// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIControllerBase.h"

void AAIControllerBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotaion) const
{
	DeterminAISightPerceptionViewPoint(OutLocation, OutRotaion);
}
