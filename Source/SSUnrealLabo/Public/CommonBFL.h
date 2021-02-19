// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "CommonBFL.generated.h"

/**
 * 
 */
UCLASS()
class SSUNREALLABO_API UCommonBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, DisplayName = "Open File Dialog", Category = "CommonBFL")
	static void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, const bool Flags, TArray<FString>& OutFilePaths);

	UFUNCTION(BlueprintCallable, DisplayName = "Save File Dialog", Category = "CommonBFL")
	static void SaveFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, const bool Flags, TArray<FString>& OutFilePaths);
};
