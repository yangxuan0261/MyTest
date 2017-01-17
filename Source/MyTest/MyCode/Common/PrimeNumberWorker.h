
class UMyGameInstance;

//~~~~~ Multi Threading ~~~
class FPrimeNumberWorker : public FRunnable
{
	static  FPrimeNumberWorker* Runnable;
	FRunnableThread* Thread;
	TArray<uint32>* PrimeNumbers;
	UMyGameInstance* mGameIns;
	FThreadSafeCounter StopTaskCounter; //用于多线程间的判断交互，volatile int32 Counter;
	int32 FindNextPrimeNumber();

    FCriticalSection QueueCritical; //互斥锁
    FEvent* ThreadSuspendedEvent;   //线程悬挂和唤醒事件

public:
	bool IsFinished();
    void Suspend();
    void Resume();

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