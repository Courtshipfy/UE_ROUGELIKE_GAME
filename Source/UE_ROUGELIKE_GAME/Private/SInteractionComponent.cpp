// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameInterface.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	FVector EyeLocation;
	FRotator EyeRotation;
	//MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);
	PlayerController->GetPlayerViewPoint(EyeLocation,EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	FHitResult Hit;
	bool bBlockHit = GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End,ObjectQueryParams);

	AActor* HitActor = Hit.GetActor();
	if(HitActor)
	{
		if(HitActor->Implements<USGameInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);

			ISGameInterface::Execute_Interact(HitActor,MyPawn);
		}
	}

	FColor LineColor = bBlockHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(),EyeLocation,End,LineColor,false,2.0f,0,2.0f);
}

