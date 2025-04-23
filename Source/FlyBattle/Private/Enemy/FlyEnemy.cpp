// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/Enemy/FlyEnemy.h"


// Sets default values
AFlyEnemy::AFlyEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
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

