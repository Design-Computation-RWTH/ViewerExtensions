// Copyright Epic Games, Inc. All Rights Reserved.

#include "ViewerExtensionsBPLibrary.h"
#include "ViewerExtensions.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "UObject/ScriptDelegates.h"

UViewerExtensionsBPLibrary::UViewerExtensionsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UViewerExtensionsBPLibrary::ViewerExtensionsSampleFunction(float Param)
{
	return -1;
}

bool UViewerExtensionsBPLibrary::CreateWidgetInNewWindow(UClass * UMG, UObject * Owner, int ResX, int ResY, FString WindowTitle, bool SupportMinimize,
	bool SupportMaximize, bool SupportResize, bool AlwaysOnTop)
{

	// Check if UClass is of Class UserWidget
	if (UKismetMathLibrary::ClassIsChildOf(UMG, UUserWidget::StaticClass()))
	{

		UWorld* World = Owner->GetWorld();
		// Todo: Create function setting the value for "IsTopmost.." depending on Play is in Engine Viewport (Otherwise there is a crash)
		// Create a new window

		UUserWidget* WidgetToCreate{};
		WidgetToCreate = UWidgetBlueprintLibrary::Create(World, UMG, ((APlayerController*)nullptr));

		auto NewWindow = SNew(SWindow)
			.Title(FText::FromString(WindowTitle))
			.ClientSize(FVector2D(ResX, ResY))
			.SupportsMinimize(SupportMinimize)
			.SupportsMaximize(SupportMaximize)
			.UserResizeBorder(SupportResize)
			.IsTopmostWindow(AlwaysOnTop)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
			];


		FSlateApplication::Get().AddWindow(NewWindow, true);
		NewWindow->SetContent(WidgetToCreate->TakeWidget());

		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Selected Class was not a Widget"));
		return false;
	};
}


