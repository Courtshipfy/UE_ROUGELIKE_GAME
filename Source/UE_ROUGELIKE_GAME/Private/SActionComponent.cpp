// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionComponent.h"

#include "SAction.h"

USActionComponent::USActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	
}

void USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	USAction* NewAction = NewObject<USAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool USActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(USAction* action : Actions)
	{
		if(action && action->ActionName == ActionName)
		{
			action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool USActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for(USAction* action : Actions)
	{
		if(action && action->ActionName == ActionName)
		{
			action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}


void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for(TSubclassOf<USAction> ActClass : DefaultActions)
	{
		AddAction(GetOwner(),ActClass);
	}
}


void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

