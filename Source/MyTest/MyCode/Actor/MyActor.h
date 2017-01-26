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

	virtual void PostActorCreated() override; //����ʼ������
    virtual void BeginPlay() override;
    virtual void BeginDestroy() override; //������gc��ʱ����ã��������������ã�һ�㲻��
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason); //�������ã���gc��ʱ�򻹻��ٵ���һ�Σ�һ�㲻��
    virtual void Destroyed() override; //�����ͷų�Ա������Destroy();����������

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


