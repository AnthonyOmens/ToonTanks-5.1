// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"



ATank::ATank()
{

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm -> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera -> SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);
}


void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if(PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef -> GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    
    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
    }


}

void ATank::BeginPlay()
{

    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());


}

void ATank::Move(float Value)
{

    //UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

    FVector DeltaLocation = FVector::ZeroVector;

    // X = Value * DeltaTime * Speed

    // Value is 1.0 since thats whats in the input when ever the player presses W
    // Speed just multiplys that to make it faster. Right now speed is 200, not sure what '200' does. is it 200 units per tick?
    // UGameplayStatics::GetWorldDeltaSeconds(this) is just "DeltaTime" it multiplys this all by a value like 1.000000003 to make sure that the tanks speed is not tied to FPS

    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value){

    FRotator DeltaRotation = FRotator::ZeroRotator;

    // Yaw = Value * DeltaTime * TurnRate
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);

}


// void ATank::Move2(float Value2)
// {

//     //UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

//     FVector DeltaLocation = FVector::ZeroVector;
//     DeltaLocation.Y = Value2;
//     AddActorLocalOffset(DeltaLocation);

    

// }