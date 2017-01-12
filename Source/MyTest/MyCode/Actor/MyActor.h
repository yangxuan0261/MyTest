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

    virtual void BeginPlay() override;
    virtual void BeginDestroy() override; //������gc��ʱ����ã��������������ã�һ�㲻��
    virtual void Destroyed() override; //�����ͷų�Ա������Destroy();����������

	void SetInfo(FString name);

	UFUNCTION(Exec)
	void Say();

private:
	FString mName;
    class UCoolDownComp* mCDComp;
};

