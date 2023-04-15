// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_FPSDinosaur.h"

// Sets default values
AACM_FPSDinosaur::AACM_FPSDinosaur()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DinoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	DinoMesh->SetSimulatePhysics(true);
	DinoMesh->SetNotifyRigidBodyCollision(true);
	DinoMesh->BodyInstance.SetCollisionProfileName("Forgathan");
	DinoMesh->OnComponentHit.AddDynamic(this, &AACM_FPSDinosaur::OnCompHit);

	RootComponent = DinoMesh;

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

	//Flattening Z axis, as the character model is taller than the dino
	CharacterPos = FVector(CharacterPos.X, CharacterPos.Y, 0);
	DinoPos = FVector(DinoPos.X, DinoPos.Y, 0);

	//Finding a rotation vector by comparing the Dino's position with the Character
	FRotator DinoRotation = UKismetMathLibrary::FindLookAtRotation(DinoPos, CharacterPos);
	//DinoRotation.Normalize();

	//Interpolating the rotation to smooth it out
	FRotator InterpRotation = FMath::RInterpConstantTo(GetActorRotation(), DinoRotation, FApp::GetDeltaTime(), 0.5f);

	//Adding the rotation vector to our actor
	AddActorLocalRotation(InterpRotation, false, 0, ETeleportType::None);

	//Outputting a debug message to view the actor's rotation
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), *GetActorRotation().ToString()));
}

void AACM_FPSDinosaur::DinoRush() {
	//TODO: If Dino is looking at player,(trace/raycast?), then the dino
	// will dash along the x-axis a fixed distance
}

void AACM_FPSDinosaur::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)){

		if (OtherActor->IsA(AACM_FPSProjectile::StaticClass())){
			Destroy();
		}
	}
}

