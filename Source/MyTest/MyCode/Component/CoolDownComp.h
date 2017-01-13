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
	virtual void BeginPlay() override; //组件被spawn的时候立即调用
	virtual void BeginDestroy() override; //引擎在gc的时候调用，并不是立即调用，一般不用
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason); //立即调用，可用
	// End UActorComponent Interface.

    UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
        void	SetName(FString name) { mName = name; }
private:
    FString mName;
};