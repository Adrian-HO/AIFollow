// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckBoolVariable.generated.h"

/**
Decorators are supporting nodes placed on parent-child connection, that receive notification about execution flow and can be ticked
 */

UCLASS()
class UE4AI_API UBTDecorator_CheckBoolVariable : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckBoolVariable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector BoolVariableToCheck;
	//variable to check

public:
    /** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual FString GetStaticDescription() const override;

	
};
