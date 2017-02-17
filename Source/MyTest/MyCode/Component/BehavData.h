
#pragma once

#include "BehavData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UBehavData : public UObject //特效集合
{
	GENERATED_BODY()
public:
	UBehavData();
	virtual ~UBehavData();

public:
    UFUNCTION(BlueprintCallable, Category = "UBehavData")
        void TestPrint();

    UFUNCTION(BlueprintPure, Category = "UBehavData")
        static UBehavData* CreateBehavData();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		int32		mId;//特效id
};
