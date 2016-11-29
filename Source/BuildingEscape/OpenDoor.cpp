// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	owner = GetOwner();
	
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	targets.Add( GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Missing Pressure Plate Refference"));
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if(isTargetOverlapping() && !isOpen){

		Open();
	}
	

	if (isOpen) {
		
		if (!isTargetOverlapping()) {
			Close();
		}
	}
}

bool UOpenDoor::Open() 
{
	//FRotator rot = FRotator(owner->GetActorRotation().Pitch, owner->GetActorRotation().Yaw - 80.0f, owner->GetActorRotation().Roll);
	//owner->SetActorRotation(rot);
	OnOpenRequest.Broadcast();
	return true;
}

bool UOpenDoor::Close() 
{
	//FRotator rot = FRotator(owner->GetActorRotation().Pitch, owner->GetActorRotation().Yaw + OpenAngle, owner->GetActorRotation().Roll);
	//owner->SetActorRotation(rot);
	OnCloseRequest.Broadcast();
	return true;
}

bool UOpenDoor::isTargetOverlapping()
{
	for (auto& actor : targets)
	{
		if (PressurePlate->IsOverlappingActor(actor)) {
			LastActivationTime = GetWorld()->GetTimeSeconds();
			return true;
		}
	}
	return false;
}
