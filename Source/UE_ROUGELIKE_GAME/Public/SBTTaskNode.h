// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UE_ROUGELIKE_GAME_API USBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override ;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> projectileActor;
};
