// fill out your copyright notice in the description page of project settings.


#include "Cartridge.h"
#include "Terminal.h"
#include "Gameframework/Actor.h"

void UCartridge::BeginPlay()
{
	Super::BeginPlay();
	Terminal = GetOwner()->FindComponentByClass<UTerminal>();
	checkf(Terminal, TEXT"[%s]: No Terminal Found"), *GetName())
}

void UCartridge::PrintLine(const FString& Line) const
{
	Terminal->PrintLine(Line);
}

void UCartridge::PrintLine(const TCHAR* Line) const
{
	Terminal->PrintLine(Line);
}

void UCartridge::ClearScreen() const
{
	Terminal->ClearSceen();
}