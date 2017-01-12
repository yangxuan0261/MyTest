
#include "MyTest.h"
#include "GolbalFunc.h"

UGolbalFunc::UGolbalFunc() : Super()
{
	
}

UGolbalFunc::~UGolbalFunc()
{
}

void UGolbalFunc::BeginDestroy()
{

	Super::BeginDestroy();
}


void UGolbalFunc::TestChangeLevel(FString name)
{
	UWorld* world = GWorld->GetWorld();
	UGameplayStatics::OpenLevel(world, FName(*name));
}
