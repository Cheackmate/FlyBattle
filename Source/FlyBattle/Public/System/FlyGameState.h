// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FlyGameState.generated.h"

/**
 * 
 */
UCLASS()
class FLYBATTLE_API AFlyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "FlyPlayerState")
	float Score = 0.0f;
};
