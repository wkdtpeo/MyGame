// Fill out your copyright notice in the Description page of Project Settings.


#include "PYDeveloperSettings.h"
#include "PYGlobalDataAsset.h"

void UPYDeveloperSettings::Init()
{
	if (false == AssetData.GlobalAsset.IsValid())
	{
		UPYGlobalDataAsset* Asset = Cast<UPYGlobalDataAsset>(AssetData.GlobalAsset.LoadSynchronous());
		if (Asset)
		{
			int32 test = 0;
		}
	}

	if (false == AssetData.GlobalAsset2.IsValid())
	{
		UPYGlobalDataAsset* Asset = Cast<UPYGlobalDataAsset>(AssetData.GlobalAsset2.LoadSynchronous());
		if (Asset)
		{
			int32 test = 0;
		}
	}

	if (false == GlobalAssetMain.IsValid())
	{
		UPYGlobalDataAsset* Asset = Cast<UPYGlobalDataAsset>(GlobalAssetMain.LoadSynchronous());
		if (Asset)
		{
			int32 test = 0;
		}
	}
}

FName UPYDeveloperSettings::GetCategoryName() const
{
	return FName(TEXT("ProjectY"));
}
