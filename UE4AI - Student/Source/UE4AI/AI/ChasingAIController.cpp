// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "UObject/UObjectGlobals.h"
//https://docs.unrealengine.com/en-US/Engine/ArtificialIntelligence/AIDebugging/index.html
AChasingAIController::AChasingAIController()
{
	//CREATE the PerceptionComponent using CreateDefaultSubobject<>()
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>( "perception");

	//CREATE the SightConfig using CreateDefaultSubobject<>()
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	//SET SightConfig->DetectionByAffiliation.bDetectEnemies to true
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	//SET SightConfig->DetectionByAffiliation.bDetectNeutrals to true
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	//SET SightConfig->DetectionByAffiliation.bDetectFriendlies to true
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	SightConfig->SightRadius = 1000;
	SightConfig->LoseSightRadius = 1500;
	SightConfig->PeripheralVisionAngleDegrees = 130.f;

	//CALL ConfigureSense() on PerceptionComponent passing in *SightConfig
	PerceptionComponent->ConfigureSense(*SightConfig);
	//CALL SetDominantSense() on PerceptionComponent passing in SightConfig->GetSenseImplementation()
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	//SUBSCRIBE to the PerceptionComponent's OnTargetPerceptionUpdated, passing in this, &AChasingAIController::OnTargetPerceptionUpdate
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AChasingAIController::OnTargetPerceptionUpdate);

}

void AChasingAIController::OnPossess(APawn * InPawn)
{
	//CALL Super::OnPossess() passing in InPawn
	Super::OnPossess(InPawn);
	//IF BehaviorTree NOT nullptr
	if (BehaviorTree)
		RunBehaviorTree(BehaviorTree);
		//CALL RunBehaviorTree() passing in this classes BehaviorTree
	//ENDIF
}

void AChasingAIController::OnTargetPerceptionUpdate(AActor * Actor, FAIStimulus Stimulus)
{
	//IF Actor NOT nullptr
	if (Actor)
	{
		LastKnownPlayerPosition = Stimulus.StimulusLocation;
		bCanSeePlayer = Stimulus.WasSuccessfullySensed();
	}
		//SET LastKnownPlayerPosition to  Stimulus.StimulusLocation
        //SET bCanSeePlayer to return value of Stimulus.WasSuccessfullySensed()
    //ENDIF


    //DEBUG
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
	//ENDIF
}
