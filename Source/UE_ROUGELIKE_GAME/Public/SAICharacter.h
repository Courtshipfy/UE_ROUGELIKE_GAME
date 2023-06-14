// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "SAICharacter.generated.h"

UCLASS()
class UE_ROUGELIKE_GAME_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ASAICharacter();
protected:

	//UPROPERTY(VisibleAnywhere)
	//UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSensing(APawn* Pawn);

	virtual void PostInitializeComponents() override;

};
