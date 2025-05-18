// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

class ASCharacter;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API ASPlayerController : public APlayerController
{
protected:
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleTurn(const FInputActionValue& InputActionValue);
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionTurn = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input| Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	
private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	GENERATED_BODY()

	UPROPERTY()
	ASCharacter* PlayerCharacter = nullptr;
};
