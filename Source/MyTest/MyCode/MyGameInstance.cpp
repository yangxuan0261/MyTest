#include "MyTest.h"
#include "MyGameInstance.h"

#include "Actor/MyActor.h"
#include "Common/ItemInfoDatabase.h"
#include "Common/PrimeNumberWorker.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	mStreamMgr = new FStreamableManager();
	mDataBase = nullptr;
}

void UMyGameInstance::Init()
{
	Super::Init();
}

void UMyGameInstance::Shutdown()
{
    FPrimeNumberWorker::Shutdown();
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


void UMyGameInstance::SpawnActor(int32 num)
{
	for (int32 i = 0; i < num; i++)
	{
		AMyActor* actor = GWorld->SpawnActor<AMyActor>(mMyActorCls);
		actor->SetInfo(FString::Printf(TEXT("Robot-%d"), i+1));
		mActorVec.Add(actor);
	}
}

void UMyGameInstance::ForceGc()
{
    GWorld->GetWorld()->ForceGarbageCollection(true);
}

void UMyGameInstance::MyAsyncTask()
{
	AsyncTask(ENamedThreads::GameThread, [&]()->void{
		UE_LOG(LogMyTest, Warning, TEXT("--- UMyGameInstance::MyAsyncTask"));
		SpawnActor(3);
	});
}

void UMyGameInstance::MyAsyncSuspend()
{
    FPrimeNumberWorker::Get()->Suspend();
}

void UMyGameInstance::MyAsyncResume()
{
    FPrimeNumberWorker::Get()->Resume();
}

void UMyGameInstance::MyAsyncThread()
{
	mNumVec.Empty();
	FPrimeNumberWorker::JoyInit(mNumVec, this);
	//GetTimerManager().SetTimer(mTimer1, [&]()->void {
 //       FPrimeNumberWorker* pnw = FPrimeNumberWorker::Get();
 //       if (!pnw) return;

 //       FCriticalSection* cs = pnw->GetCriticalSection(); //获取FPrimeNumberWorker到中的互斥锁QueueCritical
 //       FScopeLock QueueLock(cs);//锁住，等作用域过后QueueLock自动析构解锁
	//	UE_LOG(LogMyTest, Warning, TEXT("--- UMyGameInstance::MyAsyncThread, mNumVec.Num=%d"), mNumVec.Num());
 //       if (pnw->IsThreadFinished())
 //           FPrimeNumberWorker::Shutdown();
	//}, 1.0f, true);
}

void UMyGameInstance::MyDefine()
{
#ifdef HELLO_WORLD
	UE_LOG(LogMyTest, Warning, TEXT("--- UMyGameInstance::MyDefine, had define macro: HELLO_WORLD"));
#endif // HELLO_WORLD
}

void UMyGameInstance::ReadConfig()
{
	if (!GConfig)
		return;

	float ValueReceived =0.f;
	GConfig->GetFloat(
		TEXT("/Script/MyTest.MyTestCharacter"),
		TEXT("FixedCameraDistance"),
		ValueReceived,
		GGameIni
	);

	FString ProjName = "";
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		ProjName,
		GGameIni
	);
	UE_LOG(LogMyTest, Warning, TEXT("--- UMyGameInstance::ReadConfig, GGameIni:%s, ValueReceived:%f, ProjName:%s"), *GGameIni, ValueReceived, *ProjName);
//LogMyTest:Warning: -- - UMyGameInstance::ReadConfig, GGameIni : F : / workplace_ue4 / MyTest / Saved / Config / Windows / Game.ini, ValueReceived : 1500.000000
}

void UMyGameInstance::WriteConfig()
{
	if (!GConfig)
		return;

	const FString WriteSection = "MyCustomSection";
	//String
	GConfig->SetString(
		*WriteSection,
		TEXT("key1"),
		TEXT("Hello world"),
		GGameIni
	);
	GConfig->Flush(false, GGameIni);

	FString MyStr = "";
	GConfig->GetString(
		*WriteSection,
		TEXT("key1"),
		MyStr,
		GGameIni
	);
	UE_LOG(LogMyTest, Warning, TEXT("--- UMyGameInstance::WriteConfig, GGameIni:%s, MyStr:%s"), *GGameIni, *MyStr);
}

void UMyGameInstance::LoadAsset(TSubclassOf<UItemInfoDatabase> dataAssetCls)
{
	if (!mDataBase)
	{
		UObject* obj = mStreamMgr->SynchronousLoad(FStringAssetReference(TEXT("ItemInfoDatabase'/Game/TopDownCPP/MyBp/MyDataBaseMgrBp.MyDataBaseMgrBp'")));
		//UItemInfoDatabase* mDataBase = NewObject<UItemInfoDatabase>(this, dataAssetCls);
		mDataBase = Cast<UItemInfoDatabase>(obj);
	}

	TArray<FStringAssetReference> ObjToLoad;
	for (int32 i = 0; i < mDataBase->MeshList.Num(); ++i)
	{
		ObjToLoad.AddUnique(mDataBase->MeshList[i].Texture.ToStringReference());
	}
	//请求异步加载
	mStreamMgr->RequestAsyncLoad(ObjToLoad, FStreamableDelegate::CreateUObject(this, &UMyGameInstance::LoadAssetCallback));
}

void UMyGameInstance::LoadAssetCallback()
{
	UE_LOG(LogMyTest, Warning, TEXT("--- UMyGameInstance::LoadAssetCallback"));
}
