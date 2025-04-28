// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlyPlayerController.h"
#include "GameFramework/Character.h"
#include "FlyCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
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
	
	// UPROPERTY(VisibleAnywhere,Category="Component")
	// USphereComponent* CollisionComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fire")
	TSubclassOf<AFlyBullet> Bullet;

	UPROPERTY(EditAnywhere,Category="Move")
	float Speed;

	UPROPERTY(EditAnywhere,Category="Sound")
	class USoundCue* GameOverCue;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* ShootCue;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* ThrusterParticleComp;

	UPROPERTY(EditAnywhere,Category="Particle")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;

public:

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "Death")
	void OnDeath();
	
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "Death")
	void OnHitResult();
	
	// UFUNCTION()
	// void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AFlyCharacter();
	
	bool bDead;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& InputActionValue);
	void Look1();
	void Look(const FInputActionValue& InputActionValue);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool GetBDead() {
		return bDead;
	}

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();


protected:

	/** Fire Input Action */  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))  
	UInputAction* FireAction;  
  
	/** Move Input Action */  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))  
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))  
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))  
	UInputMappingContext* DefaultMappingContext;

public:
	AFlyPlayerController* FlyPlayerController = nullptr;

	
};
