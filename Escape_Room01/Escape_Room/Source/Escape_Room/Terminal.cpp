// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/Application/SlateApplication.h"

#include "Cartridge.h"

constexpr TCHAR GPromt[4] = TEXT("$> ");

void UTerminal::BeginPlay()
{
	Super::BeginPlay();
	UpdateText();
	
}

void UTerminal::ActiveTerminal()
{
	FInputKeyBinding PressedBinding(EKeys::AnyKey, EInputEvent::IE_Pressed);
	PressedBinding.KeyDelegate.BindDelegate(this, &)
}