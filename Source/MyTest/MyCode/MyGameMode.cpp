#include "MyTest.h"
#include "MyGameMode.h"

AMyGameMode::AMyGameMode() : Super()
{
	////Set the hud class to use our custom HUD by default.
	//HUDClass = AStandardHUD::StaticClass();

	// use our custom PlayerController class
	//PlayerControllerClass = AMyPlayerCtrler::StaticClass();

	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

AMyGameMode::~AMyGameMode()
{
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
}

void AMyGameMode::InitGameState()
{
	Super::InitGameState();
}

void AMyGameMode::RestartPlayer(AController* NewPlayer)
{
    Super::RestartPlayer(NewPlayer);
}

void AMyGameMode::RestartGame()
{
	Super::RestartGame();
}

void AMyGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}

void AMyGameMode::solspeed()
{
	FString str = FString::Printf(TEXT("--- AMyGameMode::solspeed - %d"), 789);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

}

void AMyGameMode::solname(FString _str, int32 _num)
{
	FString str = FString::Printf(TEXT("--- %s - %d"), *_str, _num);
	UE_LOG(LogMyTest, Warning, TEXT("--- %s - %d"), *_str, _num);
}
