// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"

#include "SCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ASPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void ASPlayerController::HandleTurn(const FInputActionValue& InputActionValue)
{
	const float TurningVector = InputActionValue.Get<float>();

	if (PlayerCharacter)
	{
		PlayerCharacter->AddControllerYawInput(TurningVector);
	}
}

void ASPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	PlayerCharacter = Cast<ASCharacter>(aPawn);
	checkf(PlayerCharacter, TEXT("ASPlayerController should only possess ASCharacter Pawns"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent."));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent"))

	checkf(InputMappingContext, TEXT("InputMappingContext was not specified."));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);  
	
	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this,
			&ASPlayerController::HandleMove);
	}

	if (ActionTurn)
	{
		EnhancedInputComponent->BindAction(ActionTurn, ETriggerEvent::Triggered, this, &ASPlayerController::HandleTurn);
	}
		
}

void ASPlayerController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings(); 
	Super::OnUnPossess();
}

void ASPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
