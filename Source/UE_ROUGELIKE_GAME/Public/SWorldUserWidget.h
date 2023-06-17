// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "SWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_ROUGELIKE_GAME_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentSizeBox;

	UPROPERTY(BlueprintReadOnly)
	AActor* AttachedActor;

	UPROPERTY(EditAnywhere)
	float WorldOffset;
	
};
