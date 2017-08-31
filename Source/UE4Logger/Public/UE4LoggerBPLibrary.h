// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Engine/Console.h"
#include "Engine/LocalPlayer.h"
#include "Runtime/Core/Public/Logging/LogVerbosity.h"
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

UENUM(BlueprintType)
enum ELogLevel
{
	Info,
	Warning,
	Error,
	Fatal
};

UCLASS()
class UUE4LoggerBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "UE4Logger sample test testing"), Category = "UE4LoggerTesting")
	//static float UE4LoggerSampleFunction(float Param);

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log Error", Keywords = "UE4Logger log error"), Category = "UE4Logger")
	//static void LogError(FString StringIn);

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log Error", Keywords = "UE4Logger log error"), Category = "UE4Logger")
	//static void LogWarning(FString StringIn);

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log Error", Keywords = "UE4Logger log error"), Category = "UE4Logger")
	//static void LogInfo(FString StringIn);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Log", Keywords = "UE4Logger log"), Category = "UE4Logger")
	static void Log(UObject* WorldContextObject, FString InString = "Hello", ELogLevel eLogLevel = ELogLevel::Info, bool bPrintToLog = true, bool bPrintToScreen = true, float Duration = 2.0f);
				

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, DisplayName = "Crash Engine", Keywords = "UE4Logger log fatal crash engine"), Category = "UE4Logger")
	static void CrashEngine(UObject* WorldContextObject, FString Message = "Fatal Error");

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Log Level", Keywords = "UE4Logger set log level"), Category = "UE4Logger")
	//static void SetLogLevel(ELogLevel eLogLevel);

	//UFUNCTION(BlueprintPure, meta = (DisplayName = "Log Error", Keywords = "UE4Logger get log level"), Category = "UE4Logger")
	//static ELogLevel GetLogLevel();
};
