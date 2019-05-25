// Copyright 2017-2019 Federico Santamorena, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class FUE4LoggerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};