// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "KismetTraceUtils.h"
#include "SInteractionComponent.h"
#include "AI/NavigationSystemBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArm);
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	
	this->bUseControllerRotationYaw = false;
	this->GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{  
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::PrimaryAttack()
{
	this->PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASCharacter::OnPrimaryAttackTimerComplete, 0.2f, false);
}

void ASCharacter::SecondaryAttack()
{
	this->PlayAnimMontage(AttackAnim2);

	GetWorldTimerManager().SetTimer(SecondaryTimerHandle, this, &ASCharacter::OnSecondaryAttackTimerComplete, 0.2f, false);
}

void ASCharacter::OnPrimaryAttackTimerComplete()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FHitResult HitResult;
	FHitResult DebugHitResult;
	FVector RayTraceStart = CameraComp->GetComponentLocation();
	FVector RayTraceEnd;
	float TraceLimit = 5000;
	RayTraceEnd = RayTraceStart + TraceLimit * UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector();
	const FCollisionQueryParams CollisionQueryParams;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, RayTraceStart, RayTraceEnd, ECollisionChannel::ECC_Visibility);
	DrawDebugLineTraceSingle(GetWorld(), RayTraceStart, RayTraceEnd, EDrawDebugTrace::Persistent, true, DebugHitResult, FLinearColor::Green, FLinearColor::Red, 5.0);
	FVector ProjectileEnd;
	if (HitResult.bBlockingHit)
	{
		ProjectileEnd = HitResult.ImpactPoint;
	}
	else
	{
		ProjectileEnd = RayTraceEnd;
	}
	UKismetSystemLibrary::DrawDebugPoint(GetWorld(), ProjectileEnd, 20.0, FLinearColor::Red, 5.0);
	//FRotator ProjectTileRotation = UKismetMathLibrary::FindLookAtRotation(Start, LookAtPos);
	FRotator ProjectTileRotation = FRotationMatrix::MakeFromX(ProjectileEnd - HandLocation).Rotator();
	FTransform SpawnTM = FTransform(ProjectTileRotation, HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::OnSecondaryAttackTimerComplete()
{
	//Use hand location as starting point for projectile spawn. We can easily
	//get sockets from a mesh
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_02");
	FHitResult HitResult;
	FHitResult DebugHitResult;

	//The cameras location is the start of the raycast
	FVector RayTraceStart = CameraComp->GetComponentLocation();
	FVector RayTraceEnd;
	float TraceLimit = 5000;
	//The end of the raycast is 5000 times the forward vector of the raycast.
	RayTraceEnd = RayTraceStart + TraceLimit * UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector();
	const FCollisionQueryParams CollisionQueryParams;

	//we will raycast via a line trace, where the linetrace will hit anything in the visibility channel
	GetWorld()->LineTraceSingleByChannel(HitResult, RayTraceStart, RayTraceEnd, ECollisionChannel::ECC_Visibility);

	FVector ProjectileEnd;
	if (HitResult.bBlockingHit)
	{
		ProjectileEnd = HitResult.ImpactPoint;
	}
	else
	{
		ProjectileEnd = RayTraceEnd;
	}
	//Rotators have an assignment contructor that can take an FRotationMatrix
	FRotator ProjectTileRotation = FRotationMatrix::MakeFromX(ProjectileEnd - HandLocation).Rotator();
	FTransform SpawnTM = FTransform(ProjectTileRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, SpawnTM, SpawnParams);
}