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
	RotateDino(DeltaTime);
	DinoRush(DeltaTime);
	
}

// Called to bind functionality to input
void AACM_FPSDinosaur::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AACM_FPSDinosaur::RotateDino(float DeltaTime) {

	//getting the player character and dino position every frame 
	FVector CharacterPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector DinoPos = GetActorLocation();

	//Flattening Z axis, as the character model is taller than the dino
	CharacterPos.Z = 0;
	DinoPos.Z = 0;

	//Finding a rotation vector by comparing the Dino's position with the Character
	FRotator DinoRotation = UKismetMathLibrary::FindLookAtRotation(DinoPos, CharacterPos);

	//Interpolating the rotation to smooth it out
	FRotator InterpRotation = FMath::RInterpTo(Dino->GetComponentRotation(), DinoRotation, DeltaTime, 1);

	//Adding the rotation to our Forgathan Mesh
	Dino->SetWorldRotation(InterpRotation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), *GetActorRotation().ToString()));
}

void AACM_FPSDinosaur::DinoRush(float DeltaTime) {
	//Creating a variable to hold whatever the trace hits
	FHitResult OutHit;

	//Finding the start position of the trace
	FVector Start = GetActorLocation();
	Start.Z += 50.0f; 

	//Finding the end position of the trace, and the direction to point it in
	FVector FowardVector = GetActorForwardVector();
	FVector End = ((FowardVector * 1000.f) + Start);

	//Creating a variable to handle collision events, and ignoring the event if the trace hits Forgathan
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	//Drawing a debug line to visualize the trace
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	//Actually creating the trace, and storing value (T/F) into a variable
	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	//Checking if our trace hit anything
	if (isHit){
		//Checking if the trace hits our player character
		if (OutHit.GetActor()->IsA(AACM_FPSCharacter::StaticClass())) {
			//If the trace hits the player, Forgathan will move in that direction
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Dino Rush!!!"));
			FVector Location = GetActorLocation();
			Location += GetActorForwardVector() * 500 * DeltaTime;
			SetActorLocation(Location);
		}
	}

	
}

void AACM_FPSDinosaur::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)){
		//if the dino is hit by a projectile, we delete the actor from the world
		if (OtherActor->IsA(AACM_FPSProjectile::StaticClass())){
			Destroy();
		}
	}
}

