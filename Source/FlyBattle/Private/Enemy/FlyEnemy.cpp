// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/Enemy/FlyEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy/FlyAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlyEnemy::AFlyEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetupAttachment(RootComponent);

	AIControllerClass = AFlyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AFlyEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetColor();
	GameState = Cast<AFlyGameState>(UGameplayStatics::GetGameState(this));
}

// Called every frame
void AFlyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFlyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFlyEnemy::OnDeath()
{
	// 飞机被击中的处理
	GameState->AddScore(1);
	OnEnemyDiedProcess();
	Destroy();
}

