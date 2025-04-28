// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/Enemy/FlyEnemySpawnAre.h"

#include "Components/BoxComponent.h"
#include "Enemy/FlyEnemy.h"
#include "Enemy/UAsyncEnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFlyEnemySpawnAre::AFlyEnemySpawnAre()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnInterval = 2.0f;
	MaxEnemyNum = 30;
	CurrentEnemyCount = 0;
}

// Called when the game starts or when spawned
void AFlyEnemySpawnAre::BeginPlay()
{
	Super::BeginPlay();
	Player=Cast<AFlyCharacter>( UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn,this,&AFlyEnemySpawnAre::SpawnEnemy,SpawnInterval,true,0.0f);
	EnemySpawner =  NewObject<UUAsyncEnemySpawner>();


}

void AFlyEnemySpawnAre::SpawnEnemy()
{
	if (Player->GetBDead() == false)
	{
		int32 RandomNumber = FMath::RandRange(0, Enemys.Num()-1); 
		// 生成1 ≤ RandomNumber <3 的整数，即1或2
		UE_LOG(LogTemp,Warning,TEXT("RandomNumber:%d"),RandomNumber);
	
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<AFlyEnemy>(Enemys[RandomNumber], GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);
		CurrentEnemyCount++;
	}

}

FVector AFlyEnemySpawnAre::GetGenerateLocation()
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

// Called every frame
void AFlyEnemySpawnAre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlyEnemySpawnAre::DecreaseEnemyCount()
{
	if (CurrentEnemyCount > 0)
	{
		CurrentEnemyCount--;
		UE_LOG(LogTemp,Warning,TEXT("%s"),*FString::SanitizeFloat(CurrentEnemyCount));
	}
}

