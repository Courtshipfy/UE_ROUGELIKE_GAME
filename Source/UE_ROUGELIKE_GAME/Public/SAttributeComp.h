// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HAL/ThreadHeartBeat.h"
#include "SAttributeComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChnaged,AActor*,InstigatorActor,USAttributeComp*,OwningComp,float,NewHealth,float,Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMagicChanged,float,NewMagic,float,Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_ROUGELIKE_GAME_API USAttributeComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComp();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Magic;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float HealthMax;
    
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float MagicMax;

	UFUNCTION(BlueprintCallable)
	static USAttributeComp* GetAttributes(AActor* FromActor);

	UFUNCTION()
	static bool IsActorAlive(AActor* actor);
	
	UFUNCTION(BlueprintCallable)
	bool ApplyChangeHealth(AActor*Instigator,float delta);

	UFUNCTION(BlueprintCallable)
	bool ApplyChangeMagic(float delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive();

	UFUNCTION(Exec)
	void KillSelf();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChnaged OnHealthChHangDelegated;

	UPROPERTY(BlueprintAssignable)
	FOnMagicChanged OnMagicChangedDelegate;
};
