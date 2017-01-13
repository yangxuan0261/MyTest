#pragma once
#include "CoolDownComp.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MYTEST_API UCoolDownComp : public UActorComponent
{
	GENERATED_BODY()
public:
	UCoolDownComp();
	virtual ~UCoolDownComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //�����spawn��ʱ����������
	virtual void BeginDestroy() override; //������gc��ʱ����ã��������������ã�һ�㲻��
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason); //�������ã���gc��ʱ�򻹻��ٵ���һ�Σ�һ�㲻��
	virtual void OnComponentCreated() override; //���RegisterComponentע���ʱ���������ã�һ����������ʼ������
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;//�������ã�һ����������������ֻҪDestroyComponent�ͻ���ã�
	// End UActorComponent Interface.

    UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
        void	SetName(FString name) { mName = name; }
private:
    FString mName;
};