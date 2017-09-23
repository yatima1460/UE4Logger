// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Engine/Console.h"
#include "Engine/LocalPlayer.h"
#include "Runtime/Core/Public/Logging/LogVerbosity.h"
#include <LogMacros.h>
#include "UE4LoggerBPLibrary.generated.h"

UENUM(BlueprintType, meta = (DisplayName = "Log Level", Keywords = "UE4logger log level", CompactNodeTitle = "Log Level"))
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
	//Sets the log verbosity
	//NOTE: This persists between Editor plays
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Set Log Level", Keywords = "UE4Logger log set verbosity level"), Category = "UE4-Logger|Verbosity")
	static void SetLogLevel(UObject * WorldContextObject, ELogLevel eLogLevel = ELogLevel::Error);

	//Gets the log verbosity
	//If logging is disabled it will return "None"
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Get Log Level", Keywords = "UE4Logger log get verbosity level"), Category = "UE4-Logger|Verbosity")
	static ELogLevel GetLogLevel(UObject * WorldContextObject);

	//Checks if the specified log level is suppressed because of SetLogLevel
	//Will always return True if logging is disabled
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Is Log Level Suppressed", Keywords = "UE4Logger log is suppressed verbosity level"), Category = "UE4-Logger|Verbosity")
	static bool IsLogLevelSuppressed(UObject * WorldContextObject, ELogLevel eLogLevel = ELogLevel::Info);
#pragma endregion

#pragma region utility functions
	//Logs a string with the Info log level
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Info", Keywords = "UE4Logger log info print", AdvancedDisplay = "2"), Category = "UE4-Logger|Utility Functions")
	static void LogInfo(UObject* WorldContextObject, FString InString = "Hello", bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);

	//Logs a string with the Warning log level
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Warning", Keywords = "UE4Logger log warning print", AdvancedDisplay = "2"), Category = "UE4-Logger|Utility Functions")
	static void LogWarning(UObject* WorldContextObject, FString InString = "Hello", bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);

	//Logs a string with the Error log level
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Error", Keywords = "UE4Logger log error print", AdvancedDisplay = "2"), Category = "UE4-Logger|Utility Functions")
	static void LogError(UObject* WorldContextObject, FString InString = "Hello", bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);

	//Logs a string with the Fatal log level
	//***CAUTION*** This crashes the engine!
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log Fatal (Crash Engine)", Keywords = "UE4Logger log fatal crash engine print", AdvancedDisplay = "2"), Category = "UE4-Logger|Utility Functions")
	static void LogFatal(UObject* WorldContextObject, FString Message = "Fatal Error");
#pragma endregion

#pragma region generic function
	//Logs a string
	//The log level input can be changed at runtime
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log", Keywords = "UE4Logger log print string", AdvancedDisplay = "3"), Category = "UE4-Logger")
	static void Log(UObject* WorldContextObject, FString InString = "Hello", ELogLevel eLogLevel = ELogLevel::Info, bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);
#pragma endregion
};
