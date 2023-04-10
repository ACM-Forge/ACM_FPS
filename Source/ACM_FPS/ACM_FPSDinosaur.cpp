// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_FPSDinosaur.h"

// Sets default values
AACM_FPSDinosaur::AACM_FPSDinosaur()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DinoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	check(DinoMesh != nullptr);

}

// Called when the game starts or when spawned
void AACM_FPSDinosaur::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AACM_FPSDinosaur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateDino();
	
}

// Called to bind functionality to input
void AACM_FPSDinosaur::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AACM_FPSDinosaur::RotateDino() {
	//getting the player character and dino position every frame 
	FVector CharacterPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector DinoPos = GetActorLocation();

	CharacterPos = FVector(CharacterPos.X, CharacterPos.Y, 0);
	DinoPos = FVector(DinoPos.X, DinoPos.Y, 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *DinoPos.ToString()));

	//on every frame, change the rotation
	//FRotator Rotation = FRotator(PitchValue, YawValue, RollValue);

	FRotator DinoRotation = UKismetMathLibrary::FindLookAtRotation(DinoPos, CharacterPos);
	//FQuat QuatRotation = FQuat(DinoRotation);
	AddActorLocalRotation(DinoRotation, false, 0, ETeleportType::None);
}

void AACM_FPSDinosaur::DinoRush() {
	//TODO: If Dino is looking at player,(trace implementation?), then the dino
	// will dash along the x-axis a fixed distance
}

