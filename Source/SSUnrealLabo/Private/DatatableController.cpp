// Fill out your copyright notice in the Description page of Project Settings.


#include "DatatableController.h"

TArray<UScriptStruct*> UDatatableController::GetRowStructArray()
{    
    const UEnum* ERowStructTypePtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERowStructType"), true);
    
    // Index 0 is None    
    TArray<UScriptStruct*> ValidStruct = { FPluginTableRow::StaticStruct(), FPluginTableRow::StaticStruct() };
    
    if(ERowStructTypePtr->GetMaxEnumValue() != ValidStruct.Num())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("[DBController RowStruct] ENUM and TArray are not the same length"));
    }

    return ValidStruct;
}

void UDatatableController::LoadCsvJsonAsDataTable(const FString& FilePath, const ERowStructType RowStructFlags, UDataTable* &OutTable)
{
    const UEnum* ERowStructTypePtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERowStructType"), true);

    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath) == false)
        return;

    FDateTime dateNow = FDateTime::Now();
    FString dateNowStr = FString::Printf(TEXT("%04i%02i%02i%02i%02i%02i%03"), dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond(), dateNow.GetMillisecond()); 
    FString DataTableName = ERowStructTypePtr->GetNameStringByValue((uint8)RowStructFlags) + dateNowStr;
    
    if (RowStructFlags != ERowStructType::RS_None)
    {   
        UScriptStruct* SelectedRowStruct = GetRowStructArray()[(uint8)RowStructFlags];        
        OutTable = CreateDataTable(DataTableName, SelectedRowStruct);

        FString FileStr = TEXT("");        
        FFileHelper::LoadFileToString(FileStr, *FilePath);

        if(FilePath.Right(4).ToLower().Equals(TEXT(".csv")))
        {
            OutTable->CreateTableFromCSVString(FileStr);
        }
        else if(FilePath.Right(5).ToLower().Equals(TEXT(".json")))
        {
            OutTable->CreateTableFromJSONString(FileStr);            
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("got wrong file"));
            return;
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Nope!"));
        return;
    }
}

bool UDatatableController::SaveDataTableAsCsvJson(const FString& FilePath, const UDataTable* InTable)
{
    FString DataTableStr = TEXT("");
        
    if(FilePath.Right(4).ToLower().Equals(TEXT(".csv")))
    {
        DataTableStr = InTable->GetTableAsCSV();
    }
    else if(FilePath.Right(5).ToLower().Equals(TEXT(".json")))
    {   
        DataTableStr = InTable->GetTableAsJSON();     
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Can save only csv/json files"));
        return false;
    }

    TSharedRef<TJsonWriter<TCHAR>> JsonObj = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&DataTableStr);
    FFileHelper::SaveStringToFile(*DataTableStr, *FilePath);
    return true;
}

UDataTable* UDatatableController::CreateDataTable(FString DataTableName, UScriptStruct *RowStruct)
{   
    FString AssetPath = FPaths::ProjectContentDir() + "AutoCreated/";
    AssetPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*AssetPath);
    FString PackagePath = FString("/Game/AutoCreated/") + DataTableName;
    
    UPackage *Package = CreatePackage(*PackagePath);
    UDataTable *AutoCreatedTable = NewObject<UDataTable>(Package, UDataTable::StaticClass(), *DataTableName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);    
    AutoCreatedTable->RowStruct = RowStruct;

    FAssetRegistryModule::AssetCreated(AutoCreatedTable);
    AutoCreatedTable->MarkPackageDirty();
    FString SaveFilePath = FString::Printf(TEXT("%s%s%s"), *AssetPath, *DataTableName, *FPackageName::GetAssetPackageExtension());

    UPackage::SavePackage(Package, AutoCreatedTable, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *SaveFilePath);

    return AutoCreatedTable;
}