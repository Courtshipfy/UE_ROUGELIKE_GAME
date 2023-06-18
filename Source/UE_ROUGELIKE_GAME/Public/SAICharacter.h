// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "SAttributeComp.h"
#include "SWorldUserWidget.h"
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

	UPROPERTY(EditDefaultsOnly)
	USWorldUserWidget* ActiveHealthBar;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USWorldUserWidget> HealthBarUserWidget;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USAttributeComp* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	FName TimeToHitParamName;
	
	UFUNCTION()
	void OnPawnSensing(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USAttributeComp* OwningComp,float NewHealth,float Delta);

	UFUNCTION()
	void SetTargetActor(AActor* TargetActor);

	virtual void PostInitializeComponents() override;

};
