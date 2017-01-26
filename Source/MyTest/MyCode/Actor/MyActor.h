#pragma once
#include "MyActor.generated.h"

class UCoolDownComp;

UCLASS(Blueprintable, BlueprintType)
class MYTEST_API AMyActor : public AActor
{
	GENERATED_BODY()
public:
	AMyActor();
	virtual ~AMyActor();

	virtual void PostActorCreated() override; //做初始化工作
    virtual void BeginPlay() override;
    virtual void BeginDestroy() override; //引擎在gc的时候调用，并不是立即调用，一般不用
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason); //立即调用，但gc的时候还会再调用一次，一般不用
    virtual void Destroyed() override; //用于释放成员，调用Destroy();会立即调用

	void SetInfo(FString name);

	UFUNCTION(Exec)
		void Say();

	UFUNCTION(BlueprintCallable, Category = AMyActor)
		void StartTimer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AMyActor)
		int mLeftTime;

private:
	FString mName;
    class UCoolDownComp* mCDComp;
	FTimerHandle	mTimer;
};


