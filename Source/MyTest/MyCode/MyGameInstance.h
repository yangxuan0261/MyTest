#pragma once
#include "MyGameInstance.generated.h"

class AMyActor;
class UItemInfoDatabase;

UCLASS()
class MYTEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;
	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor);
public:
	UFUNCTION(Exec)
		virtual void SpawnActor(int32 num);
    UFUNCTION(Exec)
		virtual void ForceGc();
	UFUNCTION(Exec)
		virtual void MyAsyncTask();
    UFUNCTION(Exec)
        virtual void MyAsyncSuspend();
    UFUNCTION(Exec)
        virtual void MyAsyncResume();
	UFUNCTION(Exec)
		virtual void MyAsyncThread();
	UFUNCTION(Exec)
		virtual void MyDefine();
	UFUNCTION(Exec)
		virtual void ReadConfig();
	UFUNCTION(Exec)
		virtual void WriteConfig();
	UFUNCTION(BlueprintCallable, Category = "UMyGameInstance")
		virtual void LoadAsset(TSubclassOf<UItemInfoDatabase> dataAssetCls);
	virtual void LoadAssetCallback();



public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyGameInstance")
        TSubclassOf<AMyActor>	mMyActorCls;

private:
	UItemInfoDatabase* mDataBase;
	TArray<AMyActor*> mActorVec;
	struct FStreamableManager* mStreamMgr;
	FTimerHandle	mTimer1;
	TArray<uint32> mNumVec;
};

#define GetGame()			UMyGameInstance::GetInstance()
