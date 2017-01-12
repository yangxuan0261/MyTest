#include "MyTest.h"
#include "MyGameInstance.h"

#include "Actor/MyActor.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UMyGameInstance::Init()
{
	Super::Init();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
}

bool UMyGameInstance::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	bool ret = Super::ProcessConsoleExec(Cmd, Ar, Executor);
	if (!ret)
	{
		for (AMyActor* actor : mActorVec)
			ret = actor->ProcessConsoleExec(Cmd, Ar, Executor);
	}
	UE_LOG(LogMyTest, Warning, TEXT("--- Cmd:%s exec:%d"), Cmd, (int32)ret);
	return ret;
}

void UMyGameInstance::spawnActor(int32 num)
{
	for (int32 i = 0; i < num; i++)
	{
		AMyActor* actor = GWorld->SpawnActor<AMyActor>(mMyActorCls);
		actor->SetInfo(FString::Printf(TEXT("Robot-%d"), i+1));
		mActorVec.Add(actor);
	}
}

void UMyGameInstance::forceGc()
{
    GWorld->GetWorld()->ForceGarbageCollection(true);
}
