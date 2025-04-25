// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FlyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AFlyAIController::AFlyAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlyAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AFlyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

// Called every frame
void AFlyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

