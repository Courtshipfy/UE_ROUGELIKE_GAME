// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTTaskNode.h"

#include "AIController.h"
#include "SNegativeActionButton.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if(ensure(MyController))
	{
		
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if(MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* TargectActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargectActor"));
		if(TargectActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargectActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters spParamwters;
		spParamwters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* newActor = GetWorld()->SpawnActor<AActor>(projectileActor,MuzzleLocation,MuzzleRotation,spParamwters);

		return newActor ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
