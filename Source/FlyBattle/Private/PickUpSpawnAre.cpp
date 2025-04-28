// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpSpawnAre.h"

#include "FlyCharacter.h"
#include "PickUpBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APickUpSpawnAre::APickUpSpawnAre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnInterval = 2.0f;
	MaxEnemyNum = 30;
	CurrentPickUpCount = 0;
}

void APickUpSpawnAre::SpawnPickUp()
{

	// 随机选取一个
	int RandomNum = FMath::RandRange(1,3);
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<APickUpBase>(PickUps[RandomNum], GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);
	CurrentPickUpCount++;
}

FVector APickUpSpawnAre::GetGenerateLocation()
{
	float Distance=0;
	FVector Location;
	while (Distance<MinimumDistanceToPlayer)
	{
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);
		Distance = (Location - Player->GetActorLocation()).Size();
	}

	return Location;
}

// Called when the game starts or when spawned
void APickUpSpawnAre::BeginPlay()
{
	Super::BeginPlay();
	Player=Cast<AFlyCharacter>( UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn,this,&APickUpSpawnAre::SpawnPickUp,SpawnInterval,true,0.0f);

}

// Called every frame
void APickUpSpawnAre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpSpawnAre::DecreaseEnemyCount()
{
	if (CurrentPickUpCount > 0)
	{
		CurrentPickUpCount--;
		UE_LOG(LogTemp,Warning,TEXT("%s"),*FString::SanitizeFloat(CurrentPickUpCount));
	}
}

