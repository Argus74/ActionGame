// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"

#include "SCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/BlueprintTypeConversions.h"

void ASPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (PlayerCharacter)
	{
		FRotator PlayerControllerRot(this->GetControlRotation());
		PlayerControllerRot.Pitch = 0;
		PlayerControllerRot.Roll = 0;
		
		PlayerCharacter->AddMovementInput(PlayerControllerRot.Vector(), MovementVector.Y);
		const FVector RightVector = FRotationMatrix(PlayerControllerRot).GetScaledAxis(EAxis::Y);
		PlayerCharacter->AddMovementInput(RightVector, MovementVector.X);
	}
}

void ASPlayerController::HandleTurn(const FInputActionValue& InputActionValue)
{
	const FVector2D TurningVector = InputActionValue.Get<FVector2D>();
	if (PlayerCharacter)
	{
		PlayerCharacter->AddControllerYawInput(TurningVector.X);
		this->AddPitchInput(TurningVector.Y);
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
		EnhancedInputComponent->BindAction(ActionTurn,
			ETriggerEvent::Triggered,
			this,
			&ASPlayerController::HandleTurn
			);
	}

	if (ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, PlayerCharacter, &ASCharacter::Jump);
	}
	
	UInputAction* ActionPrimaryAttack = PlayerCharacter->ActionPrimaryAttack;
	if  (ActionPrimaryAttack)
	{
		EnhancedInputComponent->BindAction(ActionPrimaryAttack,
			ETriggerEvent::Triggered,
			PlayerCharacter,
			&ASCharacter::PrimaryAttack
			);
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
