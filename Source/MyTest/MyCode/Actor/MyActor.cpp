#include "MyTest.h"
#include "MyActor.h"

#include "../Component/CoolDownComp.h"

AMyActor::AMyActor() : Super()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::AMyActor"));
    mCDComp = nullptr;
	mLeftTime = 10;
}

AMyActor::~AMyActor()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::~AMyActor, name:%s"), *mName);
}

void AMyActor::PostActorCreated()
{
	UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::PostActorCreated, name:%s"), *mName);
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::BeginPlay, name:%s"), *mName);

    if (!mCDComp)
    {
        //mCDComp = NewObject<UCoolDownComp>(this, UCoolDownComp::StaticClass());
        //mCDComp->RegisterComponent();
        //mCDComp->AttachToComponent()
        
        //mCDComp->attac
        //mCDComp->AttachToComponent(this->GetRootComponent())

    }
}

void AMyActor::BeginDestroy()
{
    UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::BeginDestroy"));
    Super::BeginDestroy();
}

void AMyActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogMyTest, Warning, TEXT("--- AMyActor::EndPlay"));
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

void AMyActor::StartTimer()
{
	auto lambda = [&]()->void {
		mLeftTime -= 1;

		if (mLeftTime < 5)
			GWorld->GetTimerManager().ClearTimer(mTimer);
	};

	auto dlg = FTimerDelegate::CreateLambda(lambda);
	//auto dlg = FTimerDelegate::CreateUObject(this, &AMyActor::TimerCount);
	GWorld->GetTimerManager().SetTimer(mTimer, dlg, 1.0f, true);
}
