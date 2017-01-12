
#pragma once

#include "GolbalFunc.generated.h"

UCLASS()
class UGolbalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UGolbalFunc();
	virtual ~UGolbalFunc();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void TestChangeLevel(FString name);

};
