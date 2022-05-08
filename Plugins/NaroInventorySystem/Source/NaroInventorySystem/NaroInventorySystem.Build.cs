// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NaroInventorySystem : ModuleRules
{
	public NaroInventorySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[] { "NaroInventorySystem/Private" });
        PublicIncludePaths.AddRange(new string[] { "NaroInventorySystem/Public" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "NetCore", });
				
		PrivateDependencyModuleNames.AddRange(new string[]{ "CoreUObject", "Engine", "Slate", "SlateCore", });
	}
}
