// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto Speed = FMath::Clamp(RelativeSpeed, -1, 1);
	auto ElevationChange = Speed * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	auto RawNewElevation = FMath::Clamp(GetRelativeRotation().Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f - Elevate: %f, ElevationChange: %f, RelativeRotation.Pitch: %f "), Time, RawNewElevation, ElevationChange, GetRelativeRotation().Pitch);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}