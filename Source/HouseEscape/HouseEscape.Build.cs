// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class HouseEscape : ModuleRules
{
	public HouseEscape(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        //Folders to work with:
        PrivateIncludePaths.AddRange(new string[] {
            "HouseEscape",
            "HouseEscape/Interactables",
            "HouseEscape/Interactables/Puzzles",
            "HouseEscape/Utils",
            "HouseEscape/Character",
            "HouseEscape/Game",
            "HouseEscape/Interactables/Items"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
