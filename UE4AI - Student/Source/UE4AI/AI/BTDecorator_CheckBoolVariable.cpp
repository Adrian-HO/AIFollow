// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckBoolVariable.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_CheckBoolVariable::UBTDecorator_CheckBoolVariable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Check Bool Variable";
	//Add filter so it can only select/accept boolean keys
	BoolVariableToCheck.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckBoolVariable, BoolVariableToCheck));
}


//TODO Week 4: /** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
bool UBTDecorator_CheckBoolVariable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//DECLARE a variable called BlackboardComp of type const UBlackboardComponent* and SET it to the return value of OwnerComp.GetBlackboardComponent()
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//IF BlackboardComp IS nullptr		
		//RETURN false
	//ENDIF

	if (BlackboardComp == nullptr)
		return false;
	//RETURN the return value of BlackboardComp->GetValueAsBool() passing in BoolVariableToCheck.SelectedKeyName
    return BlackboardComp->GetValueAsBool(BoolVariableToCheck.SelectedKeyName);//Temporary return to compile
}



FString UBTDecorator_CheckBoolVariable::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), TEXT("Bool Variable to Check"), BoolVariableToCheck.IsSet() ? *BoolVariableToCheck.SelectedKeyName.ToString():TEXT(""));
}

