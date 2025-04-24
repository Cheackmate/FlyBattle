// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FlyCharacter.generated.h"

class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class AFlyBullet;
/**
 * 
 */
UCLASS()
class FLYBATTLE_API AFlyCharacter : public ACharacter
{
	GENERATED_BODY()

	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere,Category="Fire")
	TSubclassOf<AFlyBullet> Bullet;

	UPROPERTY(EditAnywhere,Category="Move")
	float Speed;

	UPROPERTY(EditAnywhere,Category="Sound")
	USoundCue* GameOverCue;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* ThrusterParticleComp;

	UPROPERTY(EditAnywhere,Category="Particle")
	UParticleSystem* ExplosionParticle;

public:

	AFlyCharacter();
	
	bool bDead;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool GetBDead() {
		return bDead;
	}

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Move")
	void MoveForward();
};
