// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComp.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "SActionComponent.h"
#include "AbilitySystemInterface.h"
#include "SAbilitySystemComponent.h"
#include "SCharacterController.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComp;
class USActionComponent;

UCLASS()
class UE_ROUGELIKE_GAME_API ASCharacterController : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ASCharacterController();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlackHoleProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle TimerHandle_PrimaryAttack;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USAttributeComp* AttributeComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;
	

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USAttributeComp* OwningComp,float NewHealth,float Delta);

	void PostInitializeComponents() override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryAttack_TimeElapsed();

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual FVector GetPawnViewLocation() const override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
