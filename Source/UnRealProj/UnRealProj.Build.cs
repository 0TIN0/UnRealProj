// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnRealProj : ModuleRules
{
	public UnRealProj(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, ""));
		PrivateIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, ""));

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore",		// Base
			"AIModule", "GameplayTasks", "NavigationSystem", 		// AI
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
