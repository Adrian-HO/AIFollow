// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "SightAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4AI_API ASightAIController : public AAIController
{
	GENERATED_BODY()


public:

	ASightAIController();

	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
       	
	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;



	
};
