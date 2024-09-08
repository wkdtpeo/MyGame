// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PYDeveloperSettings.generated.h"


USTRUCT()
struct FPYGlobalAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataAsset> GlobalAsset;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataAsset> GlobalAsset2;
};

/**
 * 
 */
UCLASS(Config=ProjectY, Defaultconfig, meta=(DisplayName="ProjectY Developer Setting"))
class PROJECTY_API UPYDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public :
	void Init();
	virtual FName GetCategoryName() const override;
	
	UPROPERTY(EditAnywhere, Config)
	FPYGlobalAssetData AssetData;

	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UDataAsset> GlobalAssetMain;
};
