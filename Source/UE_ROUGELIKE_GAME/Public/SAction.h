// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE_ROUGELIKE_GAME_API USAction : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent)
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopAction(AActor* Instigator);
	
	UPROPERTY(EditDefaultsOnly)
	FName ActionName;
	
	UWorld* GetWorld() const override;
};
