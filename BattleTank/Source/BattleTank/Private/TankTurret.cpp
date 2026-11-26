// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// TODO: If new Yaw is far away from current yaw rotation will be change in oposite direction for exampel if current is small value like 5 and new will be 350 rotiation will be go around
	//auto CurrentYaw = GetRelativeRotation().Yaw;
	auto Speed = FMath::Clamp(RelativeSpeed, -1, 1);	
	auto RotationChange = Speed * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	//auto RawNewElevation = FMath::Clamp(GetRelativeRotation().Yaw + ElevationChange, MinRotationDegrees, MaxRotationDegrees);
	auto Rotation = GetRelativeRotation().Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
