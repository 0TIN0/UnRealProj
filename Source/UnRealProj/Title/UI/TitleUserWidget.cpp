// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUserWidget.h"
#include "Kismet/GameplayStatics.h"

void UTitleUserWidget::TitleStartEvent()
{
	UE_LOG(LogTemp, Error, TEXT("버튼클릭!"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("GothicTemple")));
}
