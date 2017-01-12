
#pragma once

#include "Tickable.h"
#include "MyGameState.generated.h"

/*
µÈ¼ÛÓÚGameStateManager
*/

UCLASS()
class MYTEST_API AMyGameState : public AGameState, public FTickableGameObject
{
	GENERATED_BODY()
public:
	AMyGameState();
	virtual ~AMyGameState();

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:
	void		StartGame();

public:


private:
	FTimerHandle	mWarmTimeHandler;
};


