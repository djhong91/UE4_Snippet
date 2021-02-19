// Fill out your copyright notice in the Description page of Project Settings.
#include "CommonBFL.h"

void UCommonBFL::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, const bool Flags, TArray<FString>& OutFilePaths)
{
    void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        if (Flags)
            DesktopPlatform->OpenFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, (uint32)1, OutFilePaths);    // Multiple Selection
        else
            DesktopPlatform->OpenFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, (uint32)0, OutFilePaths);    // Single Selection
    }
}

void UCommonBFL::SaveFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, const bool Flags, TArray<FString>& OutFilePaths)
{
    void* ParentWindowPtr = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        if (Flags)
            DesktopPlatform->SaveFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, (uint32)1, OutFilePaths);    // Multiple Selection
        else
            DesktopPlatform->SaveFileDialog(ParentWindowPtr, DialogTitle, DefaultPath, FString(""), FileTypes, (uint32)0, OutFilePaths);    // Single Selection
    }
}