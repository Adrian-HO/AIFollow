// Fill out your copyright notice in the Description page of Project Settings.


#include "SightAIController.h"
#include "Engine/Engine.h"

ASightAIController::ASightAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SightConfig->SightRadius = 1000;
	SightConfig->LoseSightRadius = 1500;
	SightConfig->PeripheralVisionAngleDegrees = 130.f;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASightAIController::OnTargetPerceptionUpdate);

}

void ASightAIController::OnTargetPerceptionUpdate(AActor * Actor, FAIStimulus Stimulus)
{
	TArray<AActor*> PerceivedActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(TSubclassOf<UAISense_Sight>(), PerceivedActors);

	bool isEntered = PerceivedActors.Contains(Actor);
	int NumberObjectSeen = PerceivedActors.Num();

	FString text = FString(Actor->GetName() + " has just " + (isEntered ? "Entered" : "Left") + 
		" the field of view. Now " + FString::FromInt(NumberObjectSeen) + " objects are visible.");

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, text);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);

}
