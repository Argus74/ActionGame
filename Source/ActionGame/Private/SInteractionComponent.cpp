// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "InputBehavior.h"
#include "SGameplayInterface.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FHitResult Hit;
	AActor* Owner = GetOwner();
	FVector ViewLocation;
	FRotator ViewRotation;
	Owner->GetActorEyesViewPoint(ViewLocation, ViewRotation);
	FVector EndPoint = ViewLocation + 1000 * ViewRotation.Vector();
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(Hit, ViewLocation, EndPoint, CollisionObjectQueryParams);
	TArray<struct FHitResult> hits;
	FCollisionShape sphere;
	sphere.SetSphere(30.f);
	GetWorld()->SweepMultiByObjectType(hits, ViewLocation, EndPoint, FQuat::Identity, CollisionObjectQueryParams, FCollisionShape(sphere));
	const float ArrowSize = 100.0f;
	const float Thickness = 5.0f;
	
	for (FHitResult result : hits)
	{
		AActor* HitActor = result.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);
				ISGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
		}
	}
	
	DrawDebugDirectionalArrow(GetWorld(), ViewLocation, EndPoint, ArrowSize, FColor::Red, false, 100.0f, 0, Thickness);
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

