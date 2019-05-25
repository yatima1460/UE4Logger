// Some copyright should be here...

using UnrealBuildTool;

public class UE4Logger : ModuleRules
{
    public UE4Logger(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add("./UE4Logger/Private");

        PublicDependencyModuleNames.Add("Core");

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
            }
        );
    }
}
