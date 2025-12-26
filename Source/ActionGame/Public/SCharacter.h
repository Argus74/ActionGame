// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USInteractionComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
UCLASS()
class ACTIONGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();
	
	USInteractionComponent* InteractionComp;
protected: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;

	FTimerHandle TimerHandle;

	FTimerHandle SecondaryTimerHandle;

	FTimerHandle TertiaryTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TertiaryProjectileClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnim;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnim2;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnim3;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Attack")
	TObjectPtr<UInputAction> ActionPrimaryAttack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Attack")
	TObjectPtr<UInputAction> ActionSecondaryAttack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Attack")
	TObjectPtr<UInputAction> ActionTertiaryAttack = nullptr;

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrimaryAttack();

	void SecondaryAttack();

	void TertiaryAttack();

	void OnPrimaryAttackTimerComplete();

	void OnSecondaryAttackTimerComplete();

	void OnTertiaryAttackTimerComplete();
	
	AActor* FireProjectileInCameraDirection(UClass* ProjectileClassToSpawn, FName SocketName);
};
