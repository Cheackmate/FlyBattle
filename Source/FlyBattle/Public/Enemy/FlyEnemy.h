// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "System/FlyGameState.h"
#include "FlyEnemy.generated.h"

class USphereComponent;

UCLASS()
class FLYBATTLE_API AFlyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* ShipSM;

	float Speed = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ExplosionParticle;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnExplosion();

	UPROPERTY(EditAnywhere, Category = "Team")
	int TeamNumber;

	AFlyGameState* GameState;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemyDiedProcess();
};
