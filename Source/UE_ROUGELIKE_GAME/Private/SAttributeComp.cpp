// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComp.h"

#include "SGameModeBase.h"

// Sets default values for this component's properties
USAttributeComp::USAttributeComp()
{
	HealthMax = 100;
	MagicMax = 300;

	Health = HealthMax;
	Magic = MagicMax;
}

USAttributeComp* USAttributeComp::GetAttributes(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<USAttributeComp>(FromActor->GetComponentByClass(USAttributeComp::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComp::IsActorAlive(AActor* actor)
{
	USAttributeComp* AttributeComp = USAttributeComp::GetAttributes(actor);
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

bool USAttributeComp::ApplyChangeHealth(AActor*Instigator,float delta)
{
	
	Health += delta;
	
	if(Health < 0) Health = 0;
	
	OnHealthChHangDelegated.Broadcast(Instigator,nullptr,Health,delta);

	//Died
	if(Health <= 0.0f)
	{
		ASGameModeBase* ASGameModeBase = GetWorld()->GetAuthGameMode<class ASGameModeBase>();
		if(ASGameModeBase)
		{
			ASGameModeBase->OnActorKilled(GetOwner(),Instigator);
		}
	}
	
	return true;
}

bool USAttributeComp::ApplyChangeMagic(float delta)
{
	Magic -= delta;

	if(Magic < 0) Magic = 0;

	OnMagicChangedDelegate.Broadcast(Magic,delta);
	
	return true;
}

bool USAttributeComp::IsAlive()
{
	return Health > 0.0f;
}



