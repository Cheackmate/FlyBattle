// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyBattle/Public/System/FlyGameModeBase.h"

void AFlyGameModeBase::StartPlay()
{
	Super::StartPlay();
	GameStartTime = GetWorld()->GetTimeSeconds(); // 记录游戏开始时间
}

float AFlyGameModeBase::GetGameTime() const
{
	return GetWorld()->GetTimeSeconds() - GameStartTime;
}
