// Copyright Epic Games, Inc. All Rights Reserved.

#include "StudyGameMode.h"
#include "StudyPlayerController.h"
#include "StudyCharacter.h"
#include "UObject/ConstructorHelpers.h"



AStudyGameMode::AStudyGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AStudyPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}