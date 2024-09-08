// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PYGlobalDataAsset.generated.h"

UENUM()
enum class EPYAssetType : uint8
{
	Global,
	Count,
};

USTRUCT()
struct FPYColorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<FName, FSlateColor> Color;
};

/**
 * 
 */
UCLASS()
class PROJECTY_API UPYGlobalDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere)
	TMap<EPYAssetType, FPYColorData> GlobalColor;
};
