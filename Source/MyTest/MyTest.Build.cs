// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyTest : ModuleRules
{
	public MyTest(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        Definitions.Add("HELLO_WORLD"); //添加 自定义的宏 或者 引擎的宏
    }
}
