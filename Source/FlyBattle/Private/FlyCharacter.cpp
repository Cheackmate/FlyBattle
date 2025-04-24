// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "FlyBullet.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Core/BuiltInCameraVariables.h"
#include "Core/BuiltInCameraVariables.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

void AFlyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PC =Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* EnhancedInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			EnhancedInput->AddMappingContext(DefaultMappingContext,0);
		}
	}
	FlyPlayerController = Cast<AFlyPlayerController>(Controller);
	UE_LOG(LogTemp,Warning,TEXT("Look before"));
}

AFlyCharacter::AFlyCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ThrusterParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrusterParticle"));
	ThrusterParticleComp->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(ShipSM);

	Speed = 2500.0f;
	bDead = false;
	
}
void AFlyCharacter::Look1()
{
	//UE_LOG(LogTemp,Warning,TEXT("Look"));
	if (!Controller) return;
	// 获取玩家控制器
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC) return;
	// 获取鼠标屏幕位置
	float MouseX, MouseY;
	PC->GetMousePosition(MouseX, MouseY);
	// 转换到世界空间
	FVector WorldLocation, WorldDirection;
	PC->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);
	//UE_LOG(LogTemp,Warning,TEXT("MouseX:%f MouseY:%f,WorldLocation:%s,WorldDirection:%s"),MouseX,MouseY,*WorldLocation.ToString(),*WorldDirection.ToString());
	// 射线检测地面
	FHitResult Hit;
	FCollisionQueryParams Params;
	FVector Start = WorldLocation;
	FVector End = Start + WorldDirection * 10000.f;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		// 计算目标方向
		FVector TargetLocation = Hit.Location;
		FVector ActorLocation = GetActorLocation();
		FVector Direction = TargetLocation - ActorLocation;
		Direction.Z = 0; // 保持水平旋转
		if (!Direction.IsNearlyZero())
		{
			// 计算并应用旋转
			FRotator NewRotation = Direction.Rotation();
			SetActorRotation(NewRotation);
		}
	}
}
void AFlyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Look1();
}

void AFlyCharacter::Move(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp,Warning,TEXT("Move"));
	// 获取二维输入向量
	const FVector2D MoveVector = InputActionValue.Get<FVector2D>();

	// 根据角色朝向计算移动方向

	// 组合移动向量ForwardVector
	AddMovementInput(FVector::RightVector , MoveVector.Y * Speed);
	AddMovementInput(FVector::ForwardVector , MoveVector.X * Speed);
	// FVector tempVector = FVector(MoveVector.X,MoveVector.Y,0.0f);
	// AddActorWorldOffset(tempVector*Speed*FApp::GetDeltaTime(), true);
}

void AFlyCharacter::Look(const FInputActionValue& InputActionValue)
{
	//UE_LOG(LogTemp,Warning,TEXT("Look"));
	if (!Controller) return;
	// 获取玩家控制器
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC) return;
	// 获取鼠标屏幕位置
	float MouseX, MouseY;
	PC->GetMousePosition(MouseX, MouseY);
	// 转换到世界空间
	FVector WorldLocation, WorldDirection;
	PC->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);
	//UE_LOG(LogTemp,Warning,TEXT("MouseX:%f MouseY:%f,WorldLocation:%s,WorldDirection:%s"),MouseX,MouseY,*WorldLocation.ToString(),*WorldDirection.ToString());
	// 射线检测地面
	FHitResult Hit;
	FCollisionQueryParams Params;
	FVector Start = WorldLocation;
	FVector End = Start + WorldDirection * 10000.f;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		// 计算目标方向
		FVector TargetLocation = Hit.Location;
		FVector ActorLocation = GetActorLocation();
		FVector Direction = TargetLocation - ActorLocation;
		Direction.Z = 0; // 保持水平旋转
		if (!Direction.IsNearlyZero())
		{
			// 计算并应用旋转
			FRotator NewRotation = Direction.Rotation();
			SetActorRotation(NewRotation);
		}
	}
}


void AFlyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings  
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {  
		// Fireing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AFlyCharacter::Fire);  
  
		// Moving  
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFlyCharacter::Move);
		
		// Looking  
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFlyCharacter::Look);
	}
	else  
	{  
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));  
	}

}

void AFlyCharacter::Fire()
{
	UE_LOG(LogTemp,Warning,TEXT("Fire !!!!!!!!!!!"));
	if (Bullet&&!bDead)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AFlyBullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParams);
		if(ShootCue)
			UGameplayStatics::PlaySoundAtLocation(this, ShootCue, GetActorLocation());
	}
}

