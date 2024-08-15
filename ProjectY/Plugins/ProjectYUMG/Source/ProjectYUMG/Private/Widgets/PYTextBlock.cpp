// Fill out your copyright notice in the Description page of Project Settings.
#include "Widgets/PYTextBlock.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "UMG"


const FText UPYTextBlock::GetPaletteCategory()
{
	return LOCTEXT("AAA", "BBB");
}

#undef LOCTEXT_NAMESPACE