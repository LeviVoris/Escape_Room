// fill out your copyright notice in the description page of project settings.


#include "cartridge.h"
#include "terminal.h"
#include "gameframework/actor.h"

void ucartridge::beginplay()
{
	super::beginplay();
	terminal = getowner()->findcomponentbyclass<uterminal>();
	checkf(terminal, text("[%s]: no terminal found"), *getname())
}

void ucartridge::printline(const fstring& line) const
{
	terminal->printline(line);
}

void ucartridge::printline(const tchar* line) const
{
	terminal->printline(line);
}

void ucartridge::clearscreen() const
{
	terminal->clearsceen();
}