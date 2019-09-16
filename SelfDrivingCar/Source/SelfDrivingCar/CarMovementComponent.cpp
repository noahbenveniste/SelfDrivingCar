// Fill out your copyright notice in the Description page of Project Settings.


#include "CarMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

void UCarMovementComponent::ApplyLinearAcceleration(float Direction, FVector SurfaceImpactNormal)
{
	// Get the owner as an AActor
	AActor * Car = this->GetOwner();
	if (!Car)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("CarMovementComponent found no owner"));
		return; 
	}

	// Get the root component of the owner, i.e. the static mesh that the force will be applied to
	USceneComponent * RootTemp = Car->GetRootComponent();
	if (!RootTemp)
	{
		UE_LOG(LogTemp, Warning, TEXT("No root component found on car"));
		return;
	}

	// Cast the RootTemp scene component to a more specific type, a static mesh component, so we can apply forces
	UStaticMeshComponent * CarBody = Cast<UStaticMeshComponent>(RootTemp);
	if (!CarBody)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not cast root component to a static mesh component"));
		return;
	}

	// Calculate the force magnitude, multiplying by positive or negative 1 to get forward or reverse motion
	auto ForceMagApplied = ForceMagnitude * Direction;

	UE_LOG(LogTemp, Warning, TEXT("Force Magnitude: %f"), ForceMagApplied);

	// To get more realistic vehicle physics, the force vector will be projected down to the road plane. First, calculate cross product of the forward vector and the ground normal.
	auto RightVector = FVector::CrossProduct(Car->GetActorForwardVector(), SurfaceImpactNormal);

	// Next, cross the right vector again with the surface impact normal
	auto ForceDirection = FVector::CrossProduct(RightVector, SurfaceImpactNormal);
	ForceDirection = ForceDirection.GetSafeNormal(); // Normalize, just in case

	// Multiply the force vector by the magnitude to get the final force that will be applied on the car body
	auto ForceApplied = ForceMagApplied * ForceDirection * -1;

	// The location to apply the force is just below and in front of the car body's center of mass
	FVector CenterOfMass = CarBody->GetCenterOfMass();
	
	// Add the x, y and z offsets. Applying the linear forces at an offset center of mass like this makes the car lean forward and back slightly when stopping/starting.
	CenterOfMass.X += CenterOfMassOffsetX;
	CenterOfMass.Y += CenterOfMassOffsetY;
	CenterOfMass.Z += CenterOfMassOffsetZ;

	// Draw a debug line to show the force vector
	if (DebugModeOn)
	{
		DrawDebugLine(GetWorld(), CenterOfMass, CenterOfMass - ForceApplied, FColor(255, 0, 0), false, -1, 0, 12.333);
	}

	// Apply the force calculated above on the car at the offset from the center of mass
	CarBody->AddForceAtLocation(ForceApplied, CenterOfMass, NAME_None);
}

void UCarMovementComponent::ApplyRotationalAcceleration(float Direction)
{
	// Get the owner as an AActor
	AActor * Car = this->GetOwner();
	if (!Car)
	{
		UE_LOG(LogTemp, Warning, TEXT("CarMovementComponent found no owner"));
		return;
	}

	// Get the root component of the owner, i.e. the static mesh that the force will be applied to
	USceneComponent * RootTemp = Car->GetRootComponent();
	if (!RootTemp)
	{
		UE_LOG(LogTemp, Warning, TEXT("No root component found on car"));
		return;
	}

	// Cast the RootTemp scene component to a more specific type, a static mesh component, so we can apply forces
	UStaticMeshComponent * CarBody = Cast<UStaticMeshComponent>(RootTemp);
	if (!CarBody)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not cast root component to a static mesh component"));
		return;
	}

	auto TorqueMagApplied = TorqueMagnitude * Direction;

	FVector TorqueDirection = CarBody->GetUpVector();

	FVector TorqueApplied = TorqueMagApplied * TorqueDirection;

	// The location to apply the force is just below and in front of the car body's center of mass
	FVector CenterOfMass = CarBody->GetCenterOfMass();

	// Add the x, y and z offsets. Applying the linear forces at an offset center of mass like this makes the car lean forward and back slightly when stopping/starting.
	CenterOfMass.X += CenterOfMassOffsetX;
	CenterOfMass.Y += CenterOfMassOffsetY;
	CenterOfMass.Z += CenterOfMassOffsetZ;

	// Draw a debug line to show the force vector
	if (DebugModeOn)
	{
		DrawDebugLine(GetWorld(), CenterOfMass, CenterOfMass - TorqueApplied, FColor(255, 0, 0), false, -1, 0, 12.333);
	}

	CarBody->AddTorqueInDegrees(TorqueApplied, NAME_None, false);
}
