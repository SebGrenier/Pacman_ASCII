#include "Game.h"
#include "ConsoleUtils.h"
using namespace std;

Game::Game(void)
	: _level(0)
{ }

Game::~Game(void)
{
	ClearLevel();
}

void Game::ClearLevel(void)
{
	if (_level)
	{
		delete _level;
	}
}

void Game::LoadLevel(const string &filename)
{
	ClearLevel();

	_level = new Level(filename);
}

void Game::Draw(void) const
{
	// Clear the console
	ConsoleUtils::ClearConsole();

	// Draw the level first, then the rest
	_level->Draw();
}