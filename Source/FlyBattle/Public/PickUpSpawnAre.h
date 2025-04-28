// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpSpawnAre.generated.h"

class AFlyCharacter;
class UBoxComponent;
class APickUpBase;

UCLASS()
class FLYBATTLE_API APickUpSpawnAre : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpSpawnAre();

	UPROPERTY(EditAnywhere,Category="Enemy")
	TArray<TSubclassOf<APickUpBase>> PickUps;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UBoxComponent* SpawnArea;

	FTimerHandle TimerHandle_Spawn;

	void SpawnPickUp();

	FVector GetGenerateLocation();

	// 距离玩家的最小距离
	float MinimumDistanceToPlayer = 300.0f;

	UPROPERTY(EditAnywhere,Category="Spawn")
	int MaxEnemyNum;

	int CurrentPickUpCount;

	float SpawnInterval;

	AFlyCharacter* Player;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DecreaseEnemyCount();
};
