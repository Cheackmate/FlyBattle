// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/FlyBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFlyBullet::AFlyBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	
	BulletSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletSM"));
	
	BulletSM->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
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

