// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "SGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_ROUGELIKE_GAME_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> MinionClass;
	
	UPROPERTY(EditDefaultsOnly)
	UEnvQuery* SpawnBotQuery;

	FTimerHandle TimerHandle_SpawnEnemies;

	UPROPERTY(EditDefaultsOnly)
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* DifficultyCurve;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	
public:

	ASGameModeBase();

	virtual void StartPlay() override;
};
