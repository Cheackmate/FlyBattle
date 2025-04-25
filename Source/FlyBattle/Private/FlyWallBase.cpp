// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyWallBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AFlyWallBase::AFlyWallBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallBox = CreateDefaultSubobject<UBoxComponent>("WallBox");
	RootComponent = WallBox;
	
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallMesh");
	WallMesh->SetupAttachment(WallBox);

}

// Called when the game starts or when spawned
void AFlyWallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

