// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlueprintFunctionLibrary.h"

#include "SAttributeComp.h"

bool USBlueprintFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	USAttributeComp* AttributeComp = USAttributeComp::GetAttributes(TargetActor);
	if (AttributeComp)
	{
		return AttributeComp->ApplyChangeHealth(DamageCauser, -DamageAmount);
	}
	return false;
}

bool USBlueprintFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			// Direction = Target - Origin
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}

	return false;
}
