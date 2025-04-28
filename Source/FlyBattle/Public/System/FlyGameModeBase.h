// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLYBATTLE_API AFlyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFlyGameModeBase()
	{
		// 初始化时间
		GameStartTime = 0.0f;
	}
	
	// 记录游戏开始时的系统时间
	float GameStartTime;
	
	virtual void StartPlay() override;
	// 获取当前游戏时间（秒）
	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetGameTime() const;
};
