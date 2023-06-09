// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE_ROUGELIKE_GAME_API ASAIController : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* EnemyBehaviorTree;
};
