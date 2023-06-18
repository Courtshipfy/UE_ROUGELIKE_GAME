// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class UE_ROUGELIKE_GAME_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly)
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category="Targeting")
	float SweepRadius;
	
	UPROPERTY(EditAnywhere, Category="Targeting")
	float SweepDistanceFallback;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnim;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> CastingEffect;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TObjectPtr<USoundBase> CastingSound;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);


public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	USAction_ProjectileAttack();
};
