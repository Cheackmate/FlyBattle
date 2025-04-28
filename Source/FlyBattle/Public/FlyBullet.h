// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class FLYBATTLE_API AFlyBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* BulletSM;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementComp;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category = "Bullet")
	void OnBulletDeath(bool bIsPlayerBullet);

	UFUNCTION()
	void NotifyActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
