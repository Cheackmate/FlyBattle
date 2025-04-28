// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/UAsyncEnemySpawner.h"

#include "Enemy/FlyEnemy.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

void UUAsyncEnemySpawner::StartAsyncSpawning(int32 NumToSpawn, const TArray<TSoftClassPtr<AFlyEnemy>>& EnemyClasses)
{
	if (EnemyClasses.Num() == 0) return;

	TotalToSpawn = NumToSpawn;
	SpawnedCount = 0;
	EnemyClassList = EnemyClasses;

	// 收集需要加载的资源路径
	TArray<FSoftObjectPath> AssetsToLoad;
	for (const auto& EnemyClass : EnemyClasses)
	{
		AssetsToLoad.Add(EnemyClass.ToSoftObjectPath());
	}

	// 异步加载敌人资源
	FStreamableManager& Streamable = UAssetManager::Get().GetStreamableManager();
	AssetLoadingHandle = Streamable.RequestAsyncLoad(
		AssetsToLoad,
		FStreamableDelegate::CreateUObject(this, &UUAsyncEnemySpawner::OnAssetsLoaded),
		FStreamableManager::AsyncLoadHighPriority
	);
}

void UUAsyncEnemySpawner::OnAssetsLoaded()
{
	// 每帧生成一个敌人直到完成
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			SpawnOneEnemy();
		});
	}
}

void UUAsyncEnemySpawner::SpawnOneEnemy()
{
	if (SpawnedCount >= TotalToSpawn) return;

	// 检查资源是否加载完成
	const int32 RandomIndex = FMath::RandRange(0, EnemyClassList.Num() - 1);
	if (EnemyClassList[RandomIndex].IsValid())
	{
		// 生成参数配置
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 生成敌人
		GetWorld()->SpawnActor<AFlyEnemy>(
			EnemyClassList[RandomIndex].Get(),
			FVector(FMath::RandPointInCircle(1000.0f), 0), // 随机生成位置
			FRotator::ZeroRotator,
			SpawnParams
		);

		SpawnedCount++;
	}

	// 继续生成下一个（分帧）
	if (SpawnedCount < TotalToSpawn)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			SpawnOneEnemy();
		});
	}
}
