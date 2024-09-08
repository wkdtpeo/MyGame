// Fill out your copyright notice in the Description page of Project Settings.


#include "PYGameInstance.h"
#include "Data/PYDeveloperSettings.h"

void UPYGameInstance::Init()
{
	Super::Init();

	UPYDeveloperSettings* DeveloperSettings = GetMutableDefault<UPYDeveloperSettings>();
	if (DeveloperSettings)
	{
		DeveloperSettings->Init();
	}
}
