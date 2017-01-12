#include "MyTest.h"
#include "MyActor.h"

#include "../Component/CoolDownComp.h"

AMyActor::AMyActor() : Super()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::AMyActor"));
    mCDComp = nullptr;
}

AMyActor::~AMyActor()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::~AMyActor, name:%s"), *mName);
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::BeginPlay, name:%s"), *mName);

    if (!mCDComp)
    {
        mCDComp = NewObject<UCoolDownComp>(this, UCoolDownComp::StaticClass());
        mCDComp->RegisterComponent();
        //mCDComp->AttachToComponent()
        this->GetRootComponent();
        //mCDComp->attac
    }
}

void AMyActor::BeginDestroy()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::BeginDestroy"));
    Super::BeginDestroy();
}

void AMyActor::Destroyed()
{
    if (mCDComp)
    {
        mCDComp->DestroyComponent();
        mCDComp = nullptr;
    }
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::Destroyed, name:%s"), *mName);
    Super::Destroyed();
}

void AMyActor::SetInfo(FString name)
{
	mName = name;
}

void AMyActor::Say()
{
	UE_LOG(LogMyTest, Warning, TEXT("name:%s, Say hello"), *mName);
}


