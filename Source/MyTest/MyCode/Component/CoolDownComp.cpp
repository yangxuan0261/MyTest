
#include "MyTest.h"
#include "CoolDownComp.h"

UCoolDownComp::UCoolDownComp()
	: Super()
{

}

UCoolDownComp::~UCoolDownComp()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- UCoolDownComp::~UCoolDownComp"));
}

void UCoolDownComp::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogMyTest, Warning, TEXT("--- UCoolDownComp::BeginPlay"));
}

void UCoolDownComp::BeginDestroy()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- UCoolDownComp::BeginDestroy"));
    Super::BeginDestroy();
}

void UCoolDownComp::DestroyComponent(bool bPromoteChildren /*= false*/)
{
    UE_LOG(LogMyTest, Warning, TEXT("--- UCoolDownComp::DestroyComponent"));
    Super::DestroyComponent(bPromoteChildren);
}

