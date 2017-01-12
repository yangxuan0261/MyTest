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
	virtual void DestroyComponent(bool bPromoteChildren = false) override; //�������ã�����
	// End UActorComponent Interface.

    UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
        void	SetName(FString name) { mName = name; }
private:
    FString mName;
};