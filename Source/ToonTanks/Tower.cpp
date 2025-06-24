// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // find the distance to the tank

    if (InFireRange())
    {
        RotateTurret(Tank -> GetActorLocation());
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    // how does casting work? Look into this

    // a value of type "APawn *" cannot be assigned to an entity of type "ATank *"
    
    // Tank = UGameplayStatics::GetPlayerPawn(this, 0);

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(InFireRange())
    {
        Fire();
    }
}


bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }

    return false;
}