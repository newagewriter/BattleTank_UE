// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("AIControlle can't find player tank"));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("AIControlle found player : %s"), *(PlayerTank->GetName()));
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
