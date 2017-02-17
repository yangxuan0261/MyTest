
#include "MyTest.h"
#include "BehavData.h"

UBehavData::UBehavData()
{
	mId = 123;
}

UBehavData::~UBehavData()
{
	UE_LOG(LogMyTest, Warning, TEXT("--- UBehaviorData::~UBehaviorData, mId:%d"), mId);
}

void UBehavData::TestPrint()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- UBehaviorData::TestPrint, mId:%d"), mId);
}

UBehavData * UBehavData::CreateBehavData()
{
    UBehavData* behavData = (UBehavData*)NewObject<UBehavData>(UBehavData::StaticClass());
    return behavData;
}
