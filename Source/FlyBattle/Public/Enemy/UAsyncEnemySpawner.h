// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UAsyncEnemySpawner.generated.h"

class AFlyEnemy;
struct FStreamableHandle;
/**
 * 
 */
UCLASS()
class FLYBATTLE_API UUAsyncEnemySpawner : public UObject
{
	GENERATED_BODY()
	
public:
	// 开始异步生成敌人（外部调用入口）
	UFUNCTION(BlueprintCallable, Category = "Enemy Spawner")
	void StartAsyncSpawning(int32 NumToSpawn, const TArray<TSoftClassPtr<AFlyEnemy>>& EnemyClasses);

private:
	// 异步加载完成回调
	void OnAssetsLoaded();

	// 单帧生成一个敌人
	void SpawnOneEnemy();

private:
	int32 TotalToSpawn = 0;       // 需要生成的总数
	int32 SpawnedCount = 0;       // 已生成的数量
	TArray<TSoftClassPtr<AFlyEnemy>> EnemyClassList; // 敌人类型列表
	TSharedPtr<FStreamableHandle> AssetLoadingHandle; // 资源加载句柄
};
