
#include "MyTest.h"
class UMyGameInstance;

//~~~~~ Multi Threading ~~~
class FPrimeNumberWorker : public FRunnable
{
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  FPrimeNumberWorker* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** The Data Ptr */
	TArray<uint32>* PrimeNumbers;

	/** The PC */
	UMyGameInstance* mGameIns;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	//The actual finding of prime numbers
	int32 FindNextPrimeNumber();

public:
	//Done?
	bool IsFinished();
	//~~~ Thread Core Functions ~~~

	//Constructor / Destructor
	FPrimeNumberWorker(TArray<uint32>& TheArray, UMyGameInstance* GameIns);
	virtual ~FPrimeNumberWorker();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();



	//~~~ Starting and Stopping Thread ~~~



	/*
	Start the thread and the worker from static (easy access)!
	This code ensures only 1 Prime Number thread will be able to run at a time.
	This function returns a handle to the newly started instance.
	*/
	static FPrimeNumberWorker* JoyInit(TArray<uint32>& TheArray, UMyGameInstance* GameIns);

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();

};