// Copyright Epic Games, Inc. All Rights Reserved.

#include "PixelCaptureCapturerRHIRDG.h"
#include "PixelCaptureInputFrameRHI.h"
#include "PixelCaptureOutputFrameRHI.h"
#include "PixelCaptureBufferFormat.h"
#include "PixelCaptureUtils.h"
#include "RenderGraphUtils.h"
#include "Async/Async.h"

TSharedPtr<FPixelCaptureCapturerRHIRDG> FPixelCaptureCapturerRHIRDG::Create(float InScale)
{
	return TSharedPtr<FPixelCaptureCapturerRHIRDG>(new FPixelCaptureCapturerRHIRDG(InScale));
}

FPixelCaptureCapturerRHIRDG::FPixelCaptureCapturerRHIRDG(float InScale)
	: Scale(InScale)
{
}

IPixelCaptureOutputFrame* FPixelCaptureCapturerRHIRDG::CreateOutputBuffer(int32 InputWidth, int32 InputHeight)
{
	const int32 Width = InputWidth * Scale;
	const int32 Height = InputHeight * Scale;

	FRHITextureCreateDesc TextureDesc = FRHITextureCreateDesc::Create2D(TEXT("FPixelCaptureCapturerRHIRDG Texture"), Width, Height, EPixelFormat::PF_B8G8R8A8);

	if (RHIGetInterfaceType() == ERHIInterfaceType::Metal)
	{
		TextureDesc.SetClearValue(FClearValueBinding::None)
			.SetFlags(ETextureCreateFlags::CPUReadback)
			.SetInitialState(ERHIAccess::CPURead);
	}
	else if (RHIGetInterfaceType() == ERHIInterfaceType::D3D11 || RHIGetInterfaceType() == ERHIInterfaceType::D3D12 || RHIGetInterfaceType() == ERHIInterfaceType::Vulkan)
	{
		TextureDesc.SetClearValue(FClearValueBinding::None)
			.SetFlags(ETextureCreateFlags::RenderTargetable)
			.SetInitialState(ERHIAccess::Present);
	}

	TextureDesc.DetermineInititialState();		

	if (RHIGetInterfaceType() == ERHIInterfaceType::Vulkan)
	{
		TextureDesc.AddFlags(ETextureCreateFlags::External);
	}
	else if (RHIGetInterfaceType() == ERHIInterfaceType::D3D11 || RHIGetInterfaceType() == ERHIInterfaceType::D3D12)
	{
		TextureDesc.AddFlags(ETextureCreateFlags::Shared);
	}

	return new FPixelCaptureOutputFrameRHI(RHICreateTexture(TextureDesc));
}

void FPixelCaptureCapturerRHIRDG::BeginProcess(const IPixelCaptureInputFrame& InputFrame, IPixelCaptureOutputFrame* OutputBuffer)
{
	checkf(InputFrame.GetType() == StaticCast<int32>(PixelCaptureBufferFormat::FORMAT_RHI), TEXT("Incorrect source frame coming into frame capture process."));

	MarkCPUWorkStart();
	MarkCPUWorkEnd();

	FRHICommandListImmediate& RHICmdList = FRHICommandListExecutor::GetImmediateCommandList();

	MarkGPUWorkStart();
	const FPixelCaptureInputFrameRHI& RHISourceFrame = StaticCast<const FPixelCaptureInputFrameRHI&>(InputFrame);
	FPixelCaptureOutputFrameRHI* OutputH264Buffer = StaticCast<FPixelCaptureOutputFrameRHI*>(OutputBuffer);
	CopyTextureRDG(RHICmdList, RHISourceFrame.FrameTexture, OutputH264Buffer->GetFrameTexture());

	MarkGPUWorkEnd();
	OnRHIStageComplete();
}

void FPixelCaptureCapturerRHIRDG::CheckComplete()
{
}

void FPixelCaptureCapturerRHIRDG::OnRHIStageComplete()
{
	EndProcess();
}
