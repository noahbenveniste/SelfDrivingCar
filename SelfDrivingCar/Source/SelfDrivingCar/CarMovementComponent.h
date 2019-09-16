// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "CarMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SELFDRIVINGCAR_API UCarMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	public:

		/* Tunable parameters */
		UPROPERTY(EDITDEFAULTSONLY)
			float ForceMagnitude = 1000000;
		UPROPERTY(EDITDEFAULTSONLY)
			float TorqueMagnitude = 1000000;
		UPROPERTY(EDITDEFAULTSONLY)
			float CenterOfMassOffsetX = 50;
		UPROPERTY(EDITDEFAULTSONLY)
			float CenterOfMassOffsetY = 0;
		UPROPERTY(EDITDEFAULTSONLY)
			float CenterOfMassOffsetZ = -10.0f;
		UPROPERTY(EDITDEFAULTSONLY)
			bool DebugModeOn = true;

		/* Callable functions */
		UFUNCTION(BlueprintCallable)
			void ApplyLinearAcceleration(float Direction, FVector SurfaceImpactNormal);
		UFUNCTION(BlueprintCallable)
			void ApplyRotationalAcceleration(float Direction);
};
