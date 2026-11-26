// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerControlle not possesing a tank"));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerControlle possesing : %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("TankController ticking"));
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) {
        return;
    }

    FVector HitLocation;
    if (GetSightRayLocation(HitLocation)) {
        GetControlledTank()->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayLocation(FVector& HitLocation) const
{
    // Find the crosshair position in pixel coordinates
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);

    auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
    FVector WorldDirection;
    if (GetLookDirection(ScreenLocation, WorldDirection)) {
        GetLookVectorHitLocation(WorldDirection, HitLocation);
        //UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *(WorldDirection.ToString()));
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X, 
        ScreenLocation.Y, 
        CameraWorldLocation, 
        LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
    FHitResult HitResult;
    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_Visibility
    )) {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0.f);
    return false;
}
