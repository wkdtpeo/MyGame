// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "PYTextBlock.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, meta=(DisplayName="PYText"))
class PROJECTYUMG_API UPYTextBlock : public UTextBlock
{
	GENERATED_BODY()

	virtual const FText GetPaletteCategory() override;
	
private:
	UPROPERTY(EditAnywhere)
	FName StringKey;
};
