// Fill out your copyright notice in the Description page of Project Settings.


#include "SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(EnemyBehaviorTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this,0);
	if(MyPawn)
	{
		FVector PawnLocation = FVector(MyPawn->GetActorLocation().X,MyPawn->GetActorLocation().Y,0);
		
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation",PawnLocation);

		GetBlackboardComponent()->SetValueAsObject("TargectActor",MyPawn);
	}
}
