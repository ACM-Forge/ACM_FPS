// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ACM_FPSDinosaur.generated.h"

UCLASS()
class ACM_FPS_API AACM_FPSDinosaur : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AACM_FPSDinosaur();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Enemy")
		UStaticMeshComponent* DinoMesh;

};
