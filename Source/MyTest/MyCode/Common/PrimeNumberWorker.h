
class UMyGameInstance;

//~~~~~ Multi Threading ~~~
class FPrimeNumberWorker : public FRunnable
{
	static  FPrimeNumberWorker* Runnable;
	FRunnableThread* Thread;
	TArray<uint32>* PrimeNumbers;
	UMyGameInstance* mGameIns;
	FThreadSafeCounter StopTaskCounter;
	int32 FindNextPrimeNumber();

    FCriticalSection QueueCritical;
    FEvent* ThreadSuspendedEvent;
    FEvent* ThreadResumedEvent;

public:
	bool IsFinished();

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
    FCriticalSection* GetCriticalSection();

    static FPrimeNumberWorker* JoyInit(TArray<uint32>& TheArray, UMyGameInstance* GameIns);
    static FPrimeNumberWorker* Get();
	static void Shutdown();
	static bool IsThreadFinished();
};