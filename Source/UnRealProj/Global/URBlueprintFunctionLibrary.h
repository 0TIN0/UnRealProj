// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Global/URGameInstance.h"
#include "URBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UURBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UR|Global")
	static void OpenLevel(FName OpenLevelName);

	static UWorld* GetCurrentPlayWorld();

	static UURGameInstance* GetURInst();

	UFUNCTION(BlueprintCallable, Category = "UR|Global")
	static void DebugSwitch();
	static bool IsDebug();
};
