// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateChasing.h"
#include "ChasingAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"



UBTService_UpdateChasing::UBTService_UpdateChasing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Update Chasing Behavior";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;

	Interval = 0.5f;
	RandomDeviation = 0.1;

	//Add filter so it can only select/accept Actor keys
	PlayerKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateChasing, PlayerKey), AActor::StaticClass());

	//Add filter so it can only select/accept boolean Keys 
	CanSeePlayerKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateChasing, CanSeePlayerKey));

}

void UBTService_UpdateChasing::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//DECLARE a variable called BlackboardComp of type UBlackboardComponent* and SET it to the return of OwnerComp.GetBlackboardComponent()
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//IF BlackboardComp IS nullptr
		//RETURN
	//ENDIF

	if (BlackboardComp == nullptr)
		return;

	//Set the Player Key on the Blackboard to the Found Player Class (this is the blueprint player type BP_Player)
	//IF !PlayerKey.IsSet()
		//DECLARE a variable called FoundActors of type TArray<AActor*>
	if (!PlayerKey.IsSet())
	{

		TArray<AActor*> FoundActor;
		//CALL UGameplayStatics::GetAllActorsOfClass() passing in GetWorld(), PlayerClass, FoundActors
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActor);

		//IF FoundActors[0] is NOT nullptr
			//CALL SetValueAsObject() on BlackboardComp passing in PlayerKey.SelectedKeyName, FoundActors[0]
		//ENDIF
	//ENDIF
		if (FoundActor[0] != nullptr)
		{
			BlackboardComp->SetValueAsObject(PlayerKey.SelectedKeyName, FoundActor[0]);
		}
	}

}

void UBTService_UpdateChasing::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//DECLARE a variable called BlackboardComp of type UBlackboardComponent* and SET it to the return of  OwnerComp.GetBlackboardComponent()
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//IF BlackboardComp IS nullptr
	if (BlackboardComp == nullptr)
	{
		//RETURN
		return;
	}
	//ENDIF

	//DECLARE a variable called AIController of type AAIController* and SET it to the return of  OwnerComp.GetAIOwner()
	AAIController* AIController = OwnerComp.GetAIOwner();
	//IF !AIController
	if (!AIController)
	{
		//RETURN
		return;
	}
	//ENDIF

	//DECLARE a variable called ChasingController of type AChasingAIController* and SET it to the Cast of AIController
	AChasingAIController* ChasingController = Cast<AChasingAIController>(AIController);
	//IF !ChasingController
	if (!ChasingController)
	{
		//RETURN
		return;
	}
	//ENDIF

	//sets the CanSeePlayer key on the BlackBoard
	//CALL SetValueAsBool() on BlackboardComp passing in CanSeePlayerKey.SelectedKeyName, ChasingController->bCanSeePlayer
	BlackboardComp->SetValueAsBool(CanSeePlayerKey.SelectedKeyName, ChasingController->bCanSeePlayer);
}
