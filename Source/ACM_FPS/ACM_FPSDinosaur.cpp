// Fill out your copyright notice in the Description page of Project Settings.


#include "ACM_FPSDinosaur.h"

// Sets default values
AACM_FPSDinosaur::AACM_FPSDinosaur()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Dino = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forgathan"));
	Dino->SetSimulatePhysics(true);
	Dino->SetNotifyRigidBodyCollision(true);
	Dino->BodyInstance.SetCollisionProfileName("Forgathan");
	Dino->OnComponentHit.AddDynamic(this, &AACM_FPSDinosaur::OnCompHit);

	RootComponent = Dino;

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
	FVector DinoPos = Dino->GetComponentLocation();

	//Flattening Z axis, as the character model is taller than the dino
	CharacterPos = FVector(CharacterPos.X, CharacterPos.Y, 0);
	DinoPos = FVector(DinoPos.X, DinoPos.Y, 0);

	//Finding a rotation vector by comparing the Dino's position with the Character
	FRotator DinoRotation = UKismetMathLibrary::FindLookAtRotation(DinoPos, CharacterPos);

	//Interpolating the rotation to smooth it out
	FRotator InterpRotation = FMath::RInterpTo(Dino->GetComponentRotation(), DinoRotation, FApp::GetDeltaTime(), 1);

	Dino->SetWorldRotation(InterpRotation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), *GetActorRotation().ToString()));
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

