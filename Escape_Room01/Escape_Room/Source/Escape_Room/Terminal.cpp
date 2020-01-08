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
	PressedBinding.KeyDelegate.BindDelegate(this, &UTerminal::OnKeyDown);

	FInputKeyBinding RepeatBinding(EKeys::AnyKey, EInputEvent::IE_Repeat);
	RepeatBinding.KeyDelegate.BindDelegate(this, &UTerminal::OnKeyDown);

	if (GetOwner()->InputComponent == nullptr) return;

	PressedBindingIndex = GetOwner()->InputComponent->KeyBindings.Emplace(MoveTemp(PressedBinding));
	RepeatBeingingIndex = GetOwner()->InputComponent->KeyBindings.Emplace(MoveTemp(RepeatBinding));
}

void UTerminal::DeactiveTerminal() const
{
	if (GetOwner()->InputComponent == nullprt) return;

	GetOwner()->InputComponent->KeyBindings.RemoveAt(RepeatBeingingIndex);
	GetOwner()->InputComponent->KeyBindings.RemoveAt(PressedBindingIndex);
}

void UTerminal::PrintLine(const FString& Line)
{
	FString Input = Line;
	FString Left, Right;
	while (Input.Split(TEXT("\n"), &Left, &Right))
	{
		Buffer.Emplace(Left);
		Input = Right;
	}
	Buffer.Emplace(Input);
	UpdateText();
}

void UTerminal::ClearScreen()
{
	Buffer.Empty();
	UpdateText();
}

