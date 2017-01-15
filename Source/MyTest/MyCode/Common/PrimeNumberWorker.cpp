#include "PrimeNumberWorker.h"

#include "../MyGameInstance.h"
//***********************************************************
//Thread Worker Starts as NULL, prior to being instanced
//		This line is essential! Compiler error without it
FPrimeNumberWorker* FPrimeNumberWorker::Runnable = NULL;

//***********************************************************

FPrimeNumberWorker::FPrimeNumberWorker(TArray<uint32>& TheArray, UMyGameInstance* GameIns)
	: mGameIns(GameIns)
	, StopTaskCounter(0)
{
	PrimeNumbers = &TheArray;

	Thread = FRunnableThread::Create(this, TEXT("FPrimeNumberWorker"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}

FPrimeNumberWorker::~FPrimeNumberWorker()
{
	delete Thread;
	Thread = NULL;
}

//Init
bool FPrimeNumberWorker::Init()
{
	PrimeNumbers->Empty();

	if (mGameIns)
	{
		//ThePC->ClientMessage("**********************************");
		//ThePC->ClientMessage("Prime Number Thread Started!");
		//ThePC->ClientMessage("**********************************");
	}
	return true;
}

//Run
uint32 FPrimeNumberWorker::Run()
{
	//Initial wait before starting
	FPlatformProcess::Sleep(0.03);

	//While not told to stop this thread 
	//		and not yet finished finding Prime Numbers
	while (StopTaskCounter.GetValue() == 0 && !IsFinished())
	{
		PrimeNumbers->Add(FindNextPrimeNumber());

		//***************************************
		//Show Incremental Results in Main Game Thread!

		//	Please note you should not create, destroy, or modify UObjects here.
		//	  Do those sort of things after all thread are completed.

		//	  All calcs for making stuff can be done in the threads
		//	     But the actual making/modifying of the UObjects should be done in main game thread.
		//ThePC->ClientMessage(FString::FromInt(PrimeNumbers->Last()));
		//***************************************

		//prevent thread from using too many resources
		FPlatformProcess::Sleep(3.0f);
	}

	//Run FPrimeNumberWorker::Shutdown() from the timer in Game Thread that is watching
	//to see when FPrimeNumberWorker::IsThreadFinished()
	return 0;
}

bool FPrimeNumberWorker::IsFinished()
{
	return PrimeNumbers->Num() == 5;
}

void FPrimeNumberWorker::Stop()
{
	StopTaskCounter.Increment();
}

FPrimeNumberWorker* FPrimeNumberWorker::JoyInit(TArray<uint32>& TheArray, UMyGameInstance* GameIns)
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FPrimeNumberWorker(TheArray, GameIns);
	}

	bool isSupport = FPlatformProcess::SupportsMultithreading();
	FString msg = isSupport ? "SupportsMultithread" : "dont SupportsMultithreading";
	UE_LOG(LogMyTest, Warning, TEXT("--- FPrimeNumberWorker::JoyInit, msg:%s"), *msg);
	return Runnable;
}

void FPrimeNumberWorker::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void FPrimeNumberWorker::Shutdown()
{
	if (Runnable)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;
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