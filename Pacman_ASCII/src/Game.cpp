#include "Game.h"
#include "ConsoleUtils.h"
#include "KeyboardUtils.h"
using namespace std;

Game::Game(void)
	: _is_running(true)
	, _level(0)
	, _pacman(0)
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
		_level = 0;
	}

	if (_pacman)
	{
		delete _pacman;
		_pacman = 0;
	}
}

void Game::LoadLevel(const string &filename)
{
	ClearLevel();

	_level = new Level(filename);
}

void Game::InitLevel(void)
{
	// Find the position of Pacman, the tokens, the ghosts and the warps
	const int height = _level->Height();
	const int width = _level->Width();

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			char chr = _level->GetCharAt(j, i);

			switch (chr)
			{
			case PACMAN_CHAR :
				_pacman = new Pacman(PACMAN_CHAR);
				_pacman->SetPosition(Vector2<int>(j, i));
				// Remove pacman from the level
				_level->SetCharAt(j, i, ' ');
				break;
			case TOKEN_CHAR :
				break;
			case GHOST_CHAR :
				break;
			default:
				break;
			}
		}
	}
}

void Game::Draw(void) const
{
	// Clear the console
	ConsoleUtils::ClearConsole();

	// Draw the level first, then the rest
	_level->Draw();
	_pacman->Draw();
}

void Game::HandleInputs(void)
{
	// Handle exit key
	if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::ESC))
	{
		_is_running = false;
		return;
	}

	// Handle Inputs for pacman
	Vector2<int> pos = _pacman->GetPosition();
	if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::LEFT_ARROW))
	{
		_pacman->SetPosition(pos + Vector2<int>(-1, 0));
	}
	else if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::RIGHT_ARROW))
	{
		_pacman->SetPosition(pos + Vector2<int>(1, 0));
	}
}
