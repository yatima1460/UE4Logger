// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UE4LoggerBPLibrary.h"
#include "UE4Logger.h"

UUE4LoggerBPLibrary::UUE4LoggerBPLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

#pragma region verbosity
void UUE4LoggerBPLibrary::SetLogLevel(UObject * WorldContextObject, ELogLevel eLogLevel)
{
#if !UE_BUILD_SHIPPING
	LogBlueprintUserMessages.SetVerbosity((ELogVerbosity::Type)eLogLevel);
#endif
}

ELogLevel UUE4LoggerBPLibrary::GetLogLevel(UObject * WorldContextObject)
{
#if !UE_BUILD_SHIPPING
	return (ELogLevel)LogBlueprintUserMessages.GetVerbosity();
#else
	return ELogLevel::None;
#endif
}

bool UUE4LoggerBPLibrary::IsLogLevelSuppressed(UObject * WorldContextObject, ELogLevel eLogLevel)
{
#if !UE_BUILD_SHIPPING
	return LogBlueprintUserMessages.IsSuppressed((ELogVerbosity::Type)eLogLevel);
#else
	return true;
#endif
}
#pragma endregion

#pragma region utility functions
void UUE4LoggerBPLibrary::LogInfo(UObject * WorldContextObject, FString InString, bool bPrintToLog, bool bPrintToScreen, float Duration)
{
	UUE4LoggerBPLibrary::Log(WorldContextObject, InString, ELogLevel::Info, bPrintToLog, bPrintToScreen, Duration);
}

void UUE4LoggerBPLibrary::LogWarning(UObject * WorldContextObject, FString InString, bool bPrintToLog, bool bPrintToScreen, float Duration)
{
	UUE4LoggerBPLibrary::Log(WorldContextObject, InString, ELogLevel::Warning, bPrintToLog, bPrintToScreen, Duration);
}

void UUE4LoggerBPLibrary::LogError(UObject * WorldContextObject, FString InString, bool bPrintToLog, bool bPrintToScreen, float Duration)
{
	UUE4LoggerBPLibrary::Log(WorldContextObject, InString, ELogLevel::Error, bPrintToLog, bPrintToScreen, Duration);
}

void UUE4LoggerBPLibrary::CrashEngine(UObject * WorldContextObject, FString Message)
{
	UUE4LoggerBPLibrary::Log(WorldContextObject, Message, ELogLevel::Fatal, true, false, 0.0f);
}
#pragma endregion

#pragma region generic function
void UUE4LoggerBPLibrary::Log(UObject* WorldContextObject, FString InString, ELogLevel eLogLevel, bool bPrintToLog, bool bPrintToScreen, float Duration)
{
	FColor logColor = FColor::White;
	switch (eLogLevel)
	{
	case ELogLevel::Warning:
		logColor = FColor::Yellow;
		break;
	case ELogLevel::Error:
	case ELogLevel::Fatal:
		logColor = FColor::Red;
		break;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	FString Prefix;
	if (World)
	{
		if (World->WorldType == EWorldType::PIE)
		{
			switch (World->GetNetMode())
			{
			case NM_Client:
				Prefix = FString::Printf(TEXT("Client %d: "), GPlayInEditorID - 1);
				break;
			case NM_DedicatedServer:
			case NM_ListenServer:
				Prefix = FString::Printf(TEXT("Server: "));
				break;
			case NM_Standalone:
				break;
			}
		}
	}

	const FString FinalDisplayString = Prefix + InString;
	FString FinalLogString = FinalDisplayString;

	static const FBoolConfigValueHelper DisplayPrintStringSource(TEXT("Kismet"), TEXT("bLogPrintStringSource"), GEngineIni);
	if (DisplayPrintStringSource)
	{
		const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
		FinalLogString = SourceObjectPrefix + FinalLogString;
	}

	if (bPrintToLog)
	{
		//can't find a better way of doing this without using a switch because of a strange compiler error
		switch (eLogLevel)
		{
		case ELogLevel::Warning:
			UE_LOG(LogBlueprintUserMessages, Warning, TEXT("%s"), *FinalLogString);
			break;
		case ELogLevel::Error:
			UE_LOG(LogBlueprintUserMessages, Error, TEXT("%s"), *FinalLogString);
			break;
		case ELogLevel::Fatal:
			UE_LOG(LogBlueprintUserMessages, Fatal, TEXT("%s"), *FinalLogString);
			break;
		default:
			UE_LOG(LogBlueprintUserMessages, Log, TEXT("%s"), *FinalLogString);
			break;
		}

		APlayerController* PC = (WorldContextObject ? UGameplayStatics::GetPlayerController(WorldContextObject, 0) : NULL);
		ULocalPlayer* LocalPlayer = (PC ? Cast<ULocalPlayer>(PC->Player) : NULL);
		if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->ViewportConsole)
		{
			LocalPlayer->ViewportClient->ViewportConsole->OutputText(FinalDisplayString);
		}
	}

#if !UE_BUILD_SHIPPING
	// Also output to the screen if possible and hide suppressed log levels
	if (bPrintToScreen && !LogBlueprintUserMessages.IsSuppressed((ELogVerbosity::Type)eLogLevel))
	{
		if (GAreScreenMessagesEnabled)
		{
			if (GConfig && Duration < 0)
			{
				GConfig->GetFloat(TEXT("Kismet"), TEXT("PrintStringDuration"), Duration, GEngineIni);
			}
			GEngine->AddOnScreenDebugMessage((uint64)-1, Duration, logColor, FinalDisplayString);
		}
		else
		{
			UE_LOG(LogBlueprint, Warning, TEXT("Screen messages disabled (!GAreScreenMessagesEnabled).  Cannot print to screen."));
		}
	}
#endif
}
#pragma endregion



