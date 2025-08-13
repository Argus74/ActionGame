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
	UCameraComponent* CameraComp;

	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Attack")
	UInputAction* ActionPrimaryAttack = nullptr;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrimaryAttack();
};
