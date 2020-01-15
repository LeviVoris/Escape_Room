// Property of Levi Voris 2020


#include "Test_Terminal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/Application/SlateApplication.h"

#include "Cartridge.h"

constexpr TCHAR GPromt[4] = TEXT("$> ");

void UTest_Terminal::BeginPlay()
{
	Super::BeginPlay();
	UpdateText();

}

void UTest_Terminal::ActiveTerminal()
{
	FInputKeyBinding PressedBinding(EKeys::AnyKey, EInputEvent::IE_Pressed);
	PressedBinding.KeyDelegate.BindDelegate(this, &UTest_Terminal::OnKeyDown);

	FInputKeyBinding RepeatBinding(EKeys::AnyKey, EInputEvent::IE_Repeat);
	RepeatBinding.KeyDelegate.BindDelegate(this, &UTest_Terminal::OnKeyDown);

	if (GetOwner()->InputComponent == nullptr) return;

	PressedBindingIndex = GetOwner()->InputComponent->KeyBindings.Emplace(MoveTemp(PressedBinding));
	RepeatBeingingIndex = GetOwner()->InputComponent->KeyBindings.Emplace(MoveTemp(RepeatBinding));
}

void UTest_Terminal::DeactiveTerminal() const
{
	if (GetOwner()->InputComponent == nullptr) return;

	GetOwner()->InputComponent->KeyBindings.RemoveAt(RepeatBeingingIndex);
	GetOwner()->InputComponent->KeyBindings.RemoveAt(PressedBindingIndex);
}

void UTest_Terminal::PrintLine(const FString& Line)
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

void UTest_Terminal::ClearScreen()
{
	Buffer.Empty();
	UpdateText();
}

FString UTest_Terminal::GetScreenText() const
{
	TArray<FString> FullTerminal = Buffer;
	FullTerminal.Add(GPromt + InputLine);

	//WrapLines
	TArray<FString> WrappedLines(WrapLines(FullTerminal));
	Truncate(WrappedLines);

	return JoinWithNewline(WrappedLines);
}

TArray<FString> UTest_Terminal::WrapLines(const TArray<FString>& Lines) const
{
	TArray<FString> WrappedLines;
	for (auto &&Line : Lines)
	{
		FString CurrentLine = Line;
		do
		{
			WrappedLines.Add(CurrentLine.Left(MaxColums));
			CurrentLine = CurrentLine.RightChop(MaxColums);
		} 
		while (CurrentLine.Len() > 0);
	}
	return WrappedLines;
}

void UTest_Terminal::Truncate(TArray<FString>& Lines) const
{
	while (Lines.Num() > MaxLines)
	{
		Lines.RemoveAt(0);
	}
}

FString UTest_Terminal::JoinWithNewline(const TArray<FString>& Lines) const
{
	FString Results;
	for (auto &&Line : Lines)
	{
		Results += +TEXT(" <br> ");
	}
	return Results;
}

void UTest_Terminal::OnKeyDown(FKey Key)
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


void UTest_Terminal::AcceptInputLine()
{
	Buffer.Emplace(GPromt + InputLine);
	auto Cartridge = GetOwner()->FindComponentByClass<UCartridge>();
	if (Cartridge != nullptr)
	{
		Cartridge->OnInput(InputLine);
	}
	InputLine = TEXT("");

}

void UTest_Terminal::BackSpace()
{
	if (InputLine.Len() > 0)
	{
		InputLine.RemoveAt(InputLine.Len() - 1);
	}
}

FString UTest_Terminal::GetKeyString(FKey Key) const
{
	const uint32* KeyCode = nullptr;
	const uint32* CharCode = nullptr;
	FInputKeyManager::Get().GetCodesFromKey(Key, KeyCode, CharCode);
	if (CharCode != nullptr)
	{
		ANSICHAR Char[2] = { static_cast<ANSICHAR>(*CharCode), '\0' };
		return ANSI_TO_TCHAR(Char);
	}

	return TEXT("");
}

void UTest_Terminal::UpdateText()
{
	TextUpdated.Broadcast(GetScreenText());
}
