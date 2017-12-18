// Copyright Jinseok Jeong 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{ 
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}

// Look for attached Physics Handle
 void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has physics handle component"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
}

//Setup Input component
 void UGrabber::SetupInputComponent()
 {
	 // Look for Input component
	 InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	 if (InputComponent)
	 {
		 UE_LOG(LogTemp, Warning, TEXT("Input component found"))
		 InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		 InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	 }
	 else
	 {
		 UE_LOG(LogTemp, Error, TEXT("%s missing Input component"), *GetOwner()->GetName());
	 }
 }

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Working"))

	// Line trace and see if reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();
	// If we hit something then attach a physics handle
	// TODO Attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release Working"))
	// TODO Release physics handle
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get player viewpoint this tick
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// See what we hit
	AActor* Actorhit = Hit.GetActor();
	if (Actorhit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(Actorhit->GetName()));
	}
	
	return Hit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
		// Move the object that we're holding

}


