#include "MyTest.h"
#include "PrimeNumberWorker.h"
#include "../MyGameInstance.h"

FPrimeNumberWorker* FPrimeNumberWorker::Runnable = nullptr;
FPrimeNumberWorker::FPrimeNumberWorker(TArray<uint32>& TheArray, UMyGameInstance* GameIns)
	: mGameIns(GameIns)
	, StopTaskCounter(0)
{
    ThreadSuspendedEvent = FPlatformProcess::GetSynchEventFromPool();
	PrimeNumbers = &TheArray;
	Thread = FRunnableThread::Create(this, TEXT("FPrimeNumberWorker"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}

FPrimeNumberWorker::~FPrimeNumberWorker()
{
	delete Thread;
	Thread = nullptr;
    FPlatformProcess::ReturnSynchEventToPool(ThreadSuspendedEvent);
    ThreadSuspendedEvent = nullptr;
}

bool FPrimeNumberWorker::Init()
{
	PrimeNumbers->Empty();
	return true;
}

uint32 FPrimeNumberWorker::Run()
{
	//Initial wait before starting
	FPlatformProcess::Sleep(0.03);
	while (StopTaskCounter.GetValue() == 0 && !IsFinished())
	{
        FScopeLock* QueueLock = new FScopeLock(&QueueCritical); //��ס
		//***************************************
        //��Ҫ spawning / modifying / deleting UObjects / AActors �ȵ�֮�����
        //���������̼߳乲����Ϣ�� modify���磺PrimeNumbers->Add
		//***************************************
        PrimeNumbers->Add(FindNextPrimeNumber());
        UE_LOG(LogMyTest, Warning, TEXT("--- FPrimeNumberWorker::Run, lock"));
        //Suspend();
        //prevent thread from using too many resources
		FPlatformProcess::Sleep(1.0f); //����˯��3����Ϊ����GameThread�е�UMyGameInstance::MyAsyncThread�е���־�򲻳���
        delete QueueLock;//����
        UE_LOG(LogMyTest, Warning, TEXT("--- FPrimeNumberWorker::Run, unlock"));
        //FPlatformProcess::Sleep(2.0f); //����˯��2����Ϊ����GameThread�л�ȡ�� ������QueueCritical ����ס
	}
    Stop();
	return 0;
}

bool FPrimeNumberWorker::IsFinished()
{
	return PrimeNumbers->Num() == 5;
}

void FPrimeNumberWorker::Suspend()
{
    ThreadSuspendedEvent->Wait();
}

void FPrimeNumberWorker::Resume()
{
    ThreadSuspendedEvent->Trigger();
}

void FPrimeNumberWorker::Stop()
{
	StopTaskCounter.Increment();
}

FPrimeNumberWorker* FPrimeNumberWorker::JoyInit(TArray<uint32>& TheArray, UMyGameInstance* GameIns)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FPrimeNumberWorker(TheArray, GameIns);
	}
	bool isSupport = FPlatformProcess::SupportsMultithreading();
	FString msg = isSupport ? "SupportsMultithread" : "dont SupportsMultithreading";
	UE_LOG(LogMyTest, Warning, TEXT("--- FPrimeNumberWorker::JoyInit, msg:%s"), *msg);
	return Runnable;
}

FPrimeNumberWorker* FPrimeNumberWorker::Get()
{
    return Runnable;
}

void FPrimeNumberWorker::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

FCriticalSection* FPrimeNumberWorker::GetCriticalSection()
{
        return &QueueCritical;
}

void FPrimeNumberWorker::Shutdown()
{
	if (Runnable)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = nullptr;
	}
}

bool FPrimeNumberWorker::IsThreadFinished()
{
	if (Runnable) return Runnable->IsFinished();
	return true;
}

int32 FPrimeNumberWorker::FindNextPrimeNumber()
{
	int32 TestPrime = 123;
	return TestPrime;
}