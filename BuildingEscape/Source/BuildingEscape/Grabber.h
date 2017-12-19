// Copyright Jinseok Jeong 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	// How far ahead of the player can we reach in cm
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Find attached Physics handle
	void FindPhysicsHandleComponent();

	// Setup Input component
	void SetupInputComponent();

	// Ray-cast and grab what's in reach
	void Grab();

	// Called when Grab is released
	void Release();

	// Return current start of reach line
	FVector GetReachLineStart();
	
	// Return current end of reach line
	FVector GetReachLineEnd();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach();

public:	
	// Sets default values for this component's properties 
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
