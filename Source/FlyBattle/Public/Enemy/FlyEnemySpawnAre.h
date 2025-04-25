// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlyCharacter.h"
#include "GameFramework/Actor.h"
#include "FlyEnemySpawnAre.generated.h"

class UBoxComponent;
class AFlyEnemy;

UCLASS()
class FLYBATTLE_API AFlyEnemySpawnAre : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlyEnemySpawnAre();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Enemy")
	TSubclassOf<AFlyEnemy> Enemy;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UBoxComponent* SpawnArea;

	FTimerHandle TimerHandle_Spawn;

	void SpawnEnemy();

	FVector GetGenerateLocation();

	// 距离玩家的最小距离
	float MinimumDistanceToPlayer = 1200.0f;

	UPROPERTY(EditAnywhere,Category="Spawn")
	int MaxEnemyNum;

	int CurrentEnemyCount;

	float SpawnInterval;

	AFlyCharacter* Player;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DecreaseEnemyCount();
};
