// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateChasing.generated.h"

/**
 * 
 */
UCLASS()
class UE4AI_API UBTService_UpdateChasing : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateChasing(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CanSeePlayerKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector LastKnownPositionKey;


	UPROPERTY(EditAnywhere, Category = PlayerClass)
	TSubclassOf<AActor> PlayerClass;
	//smartpointer is a templated class
	//takes a pointer and keeps a referents count of that pointer
	//used to hold typ of the spawn

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

private:

	bool bLastCanSeePlayer;

	
};
