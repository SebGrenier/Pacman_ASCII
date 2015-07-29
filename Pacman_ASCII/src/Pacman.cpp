#include "Pacman.h"
#include "ConsoleUtils.h"
#include <iostream>

using namespace std;

Pacman::Pacman(char chr)
	: _character(chr)
{ }

Pacman::~Pacman(void)
{}

void Pacman::Draw(void) const
{
	ConsoleUtils::SetCursorPosition(_position.x, _position.y);
	cout << _character;
}