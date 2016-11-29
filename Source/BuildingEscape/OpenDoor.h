// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorTriggered);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	bool Open();

	bool Close();

	UPROPERTY(BlueprintAssignable)
	FOnDoorTriggered OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnDoorTriggered OnCloseRequest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isOpen = false;

private:
	AActor *owner;
	

	

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorTimeDelay = 2.0f;

	UPROPERTY(EditAnywhere)
	float LastActivationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> targets;

	bool isTargetOverlapping();
};
