#pragma once
#include "MyGameInstance.generated.h"

class AMyActor;

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
		virtual void spawnActor(int32 num);
    UFUNCTION(Exec)
        virtual void forceGc();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyGameInstance")
        TSubclassOf<AMyActor>	mMyActorCls;
private:
	TArray<AMyActor*> mActorVec;
};

#define GetGame()			UMyGameInstance::GetInstance()
