#pragma once
#include "CharTypes.generated.h"


UENUM(Blueprintable, BlueprintType)
enum class CharState : uint8 //¶¯»­×´Ì¬
{
	IdleRun = 0,
	Attack,
	Injured,
	Death,
	Count,
};