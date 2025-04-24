// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/FlyBullet.h"

#include "Enemy/FlyEnemy.h"
#include "Engine/BlockingVolume.h"
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

void AFlyBullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFlyEnemy* Enemy= Cast<AFlyEnemy>(OtherActor);
	if (Enemy) {
		Enemy->OnDeath();
		Destroy();
	}
	else if (Cast<ABlockingVolume>(OtherActor)) {
		Destroy();
	}
	
}

