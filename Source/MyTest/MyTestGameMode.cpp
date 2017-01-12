// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyTest.h"
#include "MyTestGameMode.h"
#include "MyTestPlayerController.h"
#include "MyTestCharacter.h"

AMyTestGameMode::AMyTestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyTestPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}