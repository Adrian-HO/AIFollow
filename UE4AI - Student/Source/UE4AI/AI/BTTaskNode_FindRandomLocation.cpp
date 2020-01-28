// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"


UBTTaskNode_FindRandomLocation::UBTTaskNode_FindRandomLocation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find Random Location";

	//Add filter so it can only select/accept FVector keys
	DestinationVector.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTaskNode_FindRandomLocation, DestinationVector));
}


EBTNodeResult::Type UBTTaskNode_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//DECLARE a variable called BlackboardComp of type UBlackboardComponent* BlackboardComp and assign it to the return value of OwnerComp.GetBlackboardComponent()
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//IF BlackboardComp IS nullptr
	if (BlackboardComp == nullptr)
	{
		//RETURN EBTNodeResult::Failed
		return EBTNodeResult::Failed;
	}
	//ENDIF

	//DECLARE a variable called ControlledPawn of type APawn* and SET it to the return value of OwnerComp.GetAIOwner()->GetPawn()
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	//IF !ControlledPawn
	if (!ControlledPawn)
	{
		//RETURN EBTNodeResult::Failed
		return EBTNodeResult::Failed;
	}
	//ENDIF

	//GET the Navigation System
	//DECLARE a variable called NavSys of type UNavigationSystemV1* and SET it to the return value of  UNavigationSystemV1::GetCurrent(GetWorld())
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	//IF !NavSys
		//RETURN EBTNodeResult::Failed
	//ENDIF

	if (!NavSys)
		return EBTNodeResult::Failed;

	//DECLARE a variable called Result of type FNavLocation
	FNavLocation Result;
	//DECLARE a variable called Origin of type FVector and SET it to the return value of ControlledPawn->GetActorLocation()
	FVector Origin;

    //Find a random point on the NavMesh to Go to
	//DECLARE a variable called bSuccess of type bool and SET it to the return of  NavSys->GetRandomReachablePointInRadius() passing in Origin, Radius, Result
	bool bSuccess = NavSys->GetRandomReachablePointInRadius(Origin, Radius, Result);
	//IF !Success
		//RETURN EBTNodeResult::Failed
	//ENDIF
	if (!bSuccess)
		return EBTNodeResult::Failed;
    
    //Set the Destination Key value in the Blackboard to the random position on the nav mesh, the position is in Result
	//CALL SetValueAsVector() on BlackboardComp passing in DestinationVector.SelectedKeyName, Result.Location
	BlackboardComp->SetValueAsVector(DestinationVector.SelectedKeyName, Result.Location);
	//RETURN EBTNodeResult::Succeeded
	return EBTNodeResult::Succeeded;

}


FString UBTTaskNode_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), TEXT("DestinationKey"), 
		DestinationVector.IsSet() ? *DestinationVector.SelectedKeyName.ToString() : TEXT(""))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), 
			TEXT("Radius"), *FString::SanitizeFloat(Radius)));
}


