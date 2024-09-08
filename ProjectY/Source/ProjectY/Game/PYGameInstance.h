// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PYGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTY_API UPYGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	virtual void Init() override;
	
	
};
