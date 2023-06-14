// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_AttackArange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_AttackArange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComp))
	{
		AActor* TargectActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargectActor"));
		if(ensure(TargectActor))
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if(ensure(MyController))
			{
				APawn* MyPawn = MyController->GetPawn();
				if(ensure(MyPawn))
				{
					float DistanceTo = FVector::Distance(TargectActor->GetActorLocation(),MyPawn->GetActorLocation());

					bool isWithinAttack = DistanceTo < 500.f;

					bool bHasLos = false;
					if(isWithinAttack)
					{
						bHasLos = MyController->LineOfSightTo(TargectActor);
					}

					BlackboardComp->SetValueAsBool(AttackSelector.SelectedKeyName,(isWithinAttack && bHasLos));
					
				}
			}
		}
	}
}
