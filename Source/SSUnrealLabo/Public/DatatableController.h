// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine.h"
#include "Misc/DateTime.h"
#include "DataTableUtils.h"
#include "CommonBFL.h"
#include "DatatableController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERowStructType : uint8
{
	RS_None = 0x00 UMETA(DisplayName = "None"),
	RS_FPluginTableRow = 0x01 UMETA(DisplayName = "FPluginTableRow")
};

USTRUCT(BlueprintType)
struct FPluginTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString TileType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TypeNum;
};

UCLASS(Blueprintable, BlueprintType)
class SSUNREALLABO_API UDatatableController : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, DisplayName = "Load CSV/JSON As DataTable", Category = "DatatableController")
	static void LoadCsvJsonAsDataTable(const FString& FilePath, const ERowStructType RowStructFlags, UDataTable* &OutTable);

	UFUNCTION(BlueprintCallable, DisplayName = "Save DataTable As CSV/JSON", Category = "DatatableController")
	static bool SaveDataTableAsCsvJson(const FString& FilePath, const UDataTable* InTable);

	UFUNCTION()
	static UDataTable* CreateDataTable(FString DataTableName, UScriptStruct *MyStruct);

	UFUNCTION()
	static TArray<UScriptStruct*> GetRowStructArray();
};
