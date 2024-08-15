// Fill out your copyright notice in the Description page of Project Settings.
#include "FKeyStringDetailCustomization.h"
#include "Editor/PropertyEditor/Public/DetailLayoutBuilder.h"

TSharedRef<IDetailCustomization> FKeyStringDetailCustomization::MakeInstance()
{
	return MakeShareable(new FKeyStringDetailCustomization);
}

void FKeyStringDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	TSharedPtr<IPropertyHandle> KeyStringHandle = DetailLayout.GetProperty(FName("KeyString"));
}
