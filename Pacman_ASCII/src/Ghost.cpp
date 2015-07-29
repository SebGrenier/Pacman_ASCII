#include "Ghost.h"
#include "ConsoleUtils.h"
#include <iostream>

using namespace std;

Ghost::Ghost(char chr)
	: _character(chr)
	, _ghost_ai(0)
{ }

Ghost::~Ghost(void)
{
	if (_ghost_ai)
	{
		delete _ghost_ai;
	}
}

void Ghost::Draw(void) const
{
	ConsoleUtils::SetCursorPosition(_position.x, _position.y);
	cout << _character;
}

void Ghost::Think(void)
{
	if (_ghost_ai == 0)
		return;

	_ghost_ai->Update();
}

void Ghost::SetAI(IGhostAI *ai)
{
	_ghost_ai = ai;
	ai->SetGhost(this);
}

IGhostAI* Ghost::GetAI(void) const
{
	return _ghost_ai;
}