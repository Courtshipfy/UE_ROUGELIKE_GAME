// Fill out your copyright notice in the Description page of Project Settings.


#include "SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComp.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	//PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComp = CreateDefaultSubobject<USAttributeComp>("AttributeComp");
	AttributeComp->OnHealthChHangDelegated.AddDynamic(this,&ASAICharacter::OnHealthChanged);

	TimeToHitParamName = "TimeToHit";
}


void ASAICharacter::OnPawnSensing(APawn* Pawn)
{
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComp* OwningComp, float NewHealth, float Delta)
{
	if(Delta < 0.0f)
	{
		if(InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName,GetWorld()->TimeSeconds);
		
		if(NewHealth <= 0.0f)
		{
			//Stop BOT
			AAIController* AIC = Cast<AAIController>(GetController());

			if(AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			//ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			//setlifespawn
			SetLifeSpan(10.0f);
		}
	}
}

void ASAICharacter::SetTargetActor(AActor* TargetActor)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject("TargectActor",TargetActor);
	}
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//PawnSensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnPawnSensing);
}
