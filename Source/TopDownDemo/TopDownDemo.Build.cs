// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownDemo : ModuleRules
{
	public TopDownDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
			{
				"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "UMG"
			}
		);

		PrivateDependencyModuleNames.AddRange(new[]
			{
				"Slate", "SlateCore", "NavigationSystem"
			}
		);
		
		PublicIncludePaths.AddRange(new[]
		{
			"TopDownDemo/Public",
			"TopDownDemo/Public/Characters",
			"TopDownDemo/Public/Components",
			"TopDownDemo/Public/Interfaces",
			"TopDownDemo/Public/ItemSystem",
			"TopDownDemo/Public/Player",
			"TopDownDemo/Public/UI"
		});
		
		PrivateIncludePaths.AddRange(new[]
		{
			"TopDownDemo/Private",
			"TopDownDemo/Private/Characters",
			"TopDownDemo/Private/Components",
			"TopDownDemo/Private/Interfaces",
			"TopDownDemo/Private/ItemSystem",
			"TopDownDemo/Private/Player",
			"TopDownDemo/Private/UI"
		});
	}
}
