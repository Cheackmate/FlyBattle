// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyPlayerState.h"

void AFlyPlayerState::ChangeHealth(float DeltaHealth)
{
	Health = FMath::Clamp(Health + DeltaHealth, 0.0f, MaxHealth);
}
