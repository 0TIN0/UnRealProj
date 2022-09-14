// Fill out your copyright notice in the Description page of Project Settings.


#include "URBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UURBlueprintFunctionLibrary::OpenLevel(FName OpenLevelName)
{
	// 현재 실행중인 월드를 얻어온다
	UWorld* CurrentWorld = GetCurrentPlayWorld();

	// 없다면 리턴
	if (!CurrentWorld)
		return;

	// 현재 월드와 이름을 넣어서 열어줌
	UGameplayStatics::OpenLevel(CurrentWorld, OpenLevelName);
}

UWorld* UURBlueprintFunctionLibrary::GetCurrentPlayWorld()
{
	UWorld* PIE = nullptr;
	UWorld* GamePreview = nullptr;

	for (FWorldContext Context : GEngine->GetWorldContexts())
	{
		switch (Context.WorldType)
		{
		case EWorldType::PIE:
			PIE = Context.World();
			break;
		case EWorldType::GamePreview:
			GamePreview = Context.World();
			break;
		default:
			break;
		}
	}

	UWorld* CurrentWorld = nullptr;

	if (nullptr != PIE)
	{
		CurrentWorld = PIE;
	}
	else if (nullptr != GamePreview)
	{
		CurrentWorld = GamePreview;
	}

	return CurrentWorld;
}

UURGameInstance* UURBlueprintFunctionLibrary::GetURInst()
{
	UURGameInstance* Inst = GetCurrentPlayWorld()->GetGameInstance<UURGameInstance>();

	if (!Inst)
	{
		UE_LOG(LogTemp, Error, TEXT("URGameInst Null!"));
		return nullptr;
	}

	return Inst;
}

void UURBlueprintFunctionLibrary::DebugSwitch()
{
	// 플레이중인 월드가 없다면 리턴
	if (nullptr == GetCurrentPlayWorld())
	{
		return;
	}
	UURGameInstance* Inst = GetCurrentPlayWorld()->GetGameInstance<UURGameInstance>();

	if (!Inst)
	{
		UE_LOG(LogTemp, Error, TEXT("URGameInst Null!"));
		return;
	}

	Inst->DebugSwitch();
}

bool UURBlueprintFunctionLibrary::IsDebug()
{
	UURGameInstance* Inst = GetCurrentPlayWorld()->GetGameInstance<UURGameInstance>();

	if (!Inst)
	{
		UE_LOG(LogTemp, Error, TEXT("URGameInst Null!"));
		return false;
	}

	return Inst->IsDebug();
}