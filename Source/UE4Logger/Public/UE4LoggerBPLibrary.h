// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Engine/Console.h"
#include "Engine/LocalPlayer.h"
#include "Runtime/Core/Public/Logging/LogVerbosity.h"
#include <LogMacros.h>
#include "UE4LoggerBPLibrary.generated.h"


/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UENUM(BlueprintType, meta = (Keywords = "UE4logger log level", CompactNodeTitle = "Log Level"))
enum ELogLevel
{
	None = 0,
	Fatal = 1,
	Error = 2,
	Warning = 3,
	Info = 5
};

UCLASS()
class UUE4LoggerBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

#pragma region verbosity
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Set Log Level", Keywords = "UE4Logger log set verbosity level"), Category = "UE4-Logger|Log Level")
	static void SetLogLevel(UObject * WorldContextObject, ELogLevel eLogLevel = ELogLevel::Error);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Get Log Level", Keywords = "UE4Logger log get verbosity level"), Category = "UE4-Logger|Log Level")
	static ELogLevel GetLogLevel(UObject * WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Is Log Level Suppressed", Keywords = "UE4Logger log is suppressed verbosity level"), Category = "UE4-Logger|Log Level")
	static bool IsLogLevelSuppressed(UObject * WorldContextObject, ELogLevel eLogLevel = ELogLevel::Info);
#pragma endregion

#pragma region utility functions
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Info", Keywords = "UE4Logger log info print", AdvancedDisplay = "2"), Category = "UE4-Logger")
	static void LogInfo(UObject* WorldContextObject, FString InString = "Hello", bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Warning", Keywords = "UE4Logger log warning print", AdvancedDisplay = "2"), Category = "UE4-Logger")
	static void LogWarning(UObject* WorldContextObject, FString InString = "Hello", bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Error", Keywords = "UE4Logger log error print", AdvancedDisplay = "2"), Category = "UE4-Logger")
	static void LogError(UObject* WorldContextObject, FString InString = "Hello", bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Fatal (Crash Engine)", Keywords = "UE4Logger log fatal crash engine print", AdvancedDisplay = "2"), Category = "UE4-Logger|Advanced")
	static void CrashEngine(UObject* WorldContextObject, FString Message = "Fatal Error");
#pragma endregion

#pragma region generic function
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log", Keywords = "UE4Logger log print string", AdvancedDisplay = "3"), Category = "UE4-Logger")
	static void Log(UObject* WorldContextObject, FString InString = "Hello", ELogLevel eLogLevel = ELogLevel::Info, bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);
#pragma endregion
};
