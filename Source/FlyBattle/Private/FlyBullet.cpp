// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/FlyBullet.h"


// Sets default values
AFlyBullet::AFlyBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

