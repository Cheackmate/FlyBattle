﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FlyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FLYBATTLE_API AFlyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "FlyPlayerState")
	float Health = 5.0f;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "FlyPlayerState")
	float MaxHealth = 5.0f;

	UFUNCTION(BlueprintCallable, Category = "FlyPlayerState")
	void ChangeHealth(float DeltaHealth);
};
