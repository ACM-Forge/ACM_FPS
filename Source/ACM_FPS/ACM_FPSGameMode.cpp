// Copyright Epic Games, Inc. All Rights Reserved.

#include "ACM_FPSGameMode.h"
#include "ACM_FPSHUD.h"
#include "ACM_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AACM_FPSGameMode::AACM_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AACM_FPSHUD::StaticClass();
}
