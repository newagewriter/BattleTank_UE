// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player : %s"), *(PlayerTank->GetName()));
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("TankController ticking"));
    if (GetPlayerTank()) {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!playerPawn) {
        UE_LOG(LogTemp, Error, TEXT("Cannot find player"));
        return nullptr;
    }
    return Cast<ATank>(playerPawn);
}
