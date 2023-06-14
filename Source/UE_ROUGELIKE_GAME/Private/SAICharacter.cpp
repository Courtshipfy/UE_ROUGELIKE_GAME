// Fill out your copyright notice in the Description page of Project Settings.


#include "SAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	//PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void ASAICharacter::OnPawnSensing(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	if(AIController)
	{
		 UBlackboardComponent* BLKComp = AIController->GetBlackboardComponent();
		if(BLKComp)
		{
			BLKComp->SetValueAsObject("TargectActor",Pawn);

			DrawDebugString(GetWorld(),GetActorLocation(),"player spotted",nullptr,FColor::Red,4.0f,true);
		}
	}
	
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//PawnSensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnPawnSensing);
}
