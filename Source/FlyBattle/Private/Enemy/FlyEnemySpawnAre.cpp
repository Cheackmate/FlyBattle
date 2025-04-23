// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/Enemy/FlyEnemySpawnAre.h"


// Sets default values
AFlyEnemySpawnAre::AFlyEnemySpawnAre()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlyEnemySpawnAre::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyEnemySpawnAre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

