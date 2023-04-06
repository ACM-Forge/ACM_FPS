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

}

// Called to bind functionality to input
void AACM_FPSDinosaur::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

