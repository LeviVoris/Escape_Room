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
	if (GetOwner()->InputComponent == nullptr) return;

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

FString UTerminal::GetScreenText() const
{
	TArray<FString> FullTerminal = Buffer;
	FullTerminal.Add(GPromt + InputLine);

	//Wrap Lines
	TArray<FString> WrappedLines(WrapLines(FullTerminal));
	Truncate(WrappedLines);

	return JoinWithNewline(WrappedLines);
}

TArray<FString> UTerminal::WrapLines(const TArray<FString>& Lines) const
{
	TArray<FString> RappedLines;
	for (auto &&Line : Line);
	{
		do
		{
			WrappedLines.Add(CurrentLine.Left(MaxColums));
			CurrentLine = CurrentLine.RightChop(MaxColums);
		} 
		while (CurrentLine.Len() > 0);
	}
	return WrappedLines;
}

void UTerminal::Truncate(TArray<FString>& Lines) const
{
	while (Lines.Num() > MaxLines)
	{
		Lines.RemoveAt(0);
	}
}

FString UTerminal::JoinWithNewline(const TArray<FString>& Lines) const
{
	FString Results;
	for (auto &&Line : Line)
	{
		Results += +TEXT(" <br> ");
	}
	return Result;
}

void UTerminal::OnKeyDown(FKey Key)
{
	if (Key == EKeys::Enter)
	{
		AcceptInputLine();
	}

	if (Key == EKeys::BackSpace)
	{
		BackSpace();
	}

	const FString KeyString = GetKeyString(Key);
	const FModifierKeysState KeyState = FSlateApplication::Get().GetModifierKeys();
	if (KeyState.IsShiftDown() || KeyState.AreCapsLocked())
	{
		InputLine += KeyString.ToUpper();
	}
	else
	{
		InputLine += KeyString.ToLower();
	}

	UpdateText();
}


void UTerminal::AcceptInputLine()
{
	Buffer.Emplace(GPromt + InputLine);
	auto Cartridge = GetOwner()->FindComponentByClass<UCartridge>();
	if (Cartridge != nullptr)
	{
		Cartridge->OnInput(InputLine);
	}
	InputLine = TEXT("");

}

void UTerminal::BackSpace()
{
	if (InputLine.Len() > 0)
	{
		InputLine.RemoveAt(InputLine.Len() - 1);
	}
}

void UTerminal::GetKeyString(FKey Key) const
{
	const uint32* KeyCode = nullptr;
	const uint32* CharCode = nullptr;
	FInputKeyManager::Get().GetCodesFromKey(Key, KeyCode, CharCode);
	if (CharCode != nullptr)
	{
		ANSICHAR Char[2] = { static_cast<ANSICHAR>(*CharCode), '\0';
		return ANSI_TO_TCHAR(Char);
	}

		return TEXT("");
}

	void UTerminal::UpdateText()
	{
		TextUpdated.Broadcast(GetScreenText();
	}