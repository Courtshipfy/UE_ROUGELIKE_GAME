// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
}

UWorld* USAction::GetWorld() const
{
	UActorComponent* outer = Cast<UActorComponent>(GetOuter());
	if(outer)
	{
		return outer->GetWorld();
	}

	return nullptr;
}
