// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Barrel = CreateDefaultSubobject<UStaticMeshComponent>("BarrelComp");
	RootComponent = Barrel;
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->Radius = 2000.0f;
	RadialForceComponent->ImpulseStrength = 900000.0f;
	RadialForceComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Barrel->OnComponentHit.AddDynamic(this,  &ASExplosiveBarrel::Explode);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASExplosiveBarrel::Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	RadialForceComponent->FireImpulse();
}


