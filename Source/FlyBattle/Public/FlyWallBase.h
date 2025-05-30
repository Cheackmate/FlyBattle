﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyWallBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
UCLASS()
class FLYBATTLE_API AFlyWallBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlyWallBase();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* WallMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UBoxComponent* WallBox;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
