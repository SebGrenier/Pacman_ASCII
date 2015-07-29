#include "Game.h"
#include "ConsoleUtils.h"
#include "KeyboardUtils.h"
#include <iostream>
using namespace std;

Game::Game(void)
	: _is_running(true)
	, _level(0)
	, _pacman(0)
	, _score(0)
	, _total_token(0)
	, _current_token(0)
	, _game_finished(false)
	, _winning(false)
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

	_ghosts.clear();
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

	Ghost new_ghost(GHOST_CHAR);
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
				++_total_token;
				break;
			case GHOST_CHAR :
				new_ghost.SetPosition(Vector2<int>(j, i));
				_ghosts.push_back(new_ghost);
				// Remove the ghost from the level
				_level->SetCharAt(j, i, ' ');
				break;
			default:
				break;
			}
		}
	}

	// Set the AI for ghosts
	const int Size = _ghosts.size();
	for (int i = 0; i < Size; ++i)
	{
		RandomGhostAI *ai = new RandomGhostAI();
		ai->Init(_level, _pacman);
		// The ghost takes ownership of the ai
		_ghosts[i].SetAI(ai);
	}
}

void Game::Update(void)
{
	const Vector2<int> pac_pos = _pacman->GetPosition();
	const char char_under_pac = _level->GetCharAt(pac_pos);
	const int nb_ghosts = _ghosts.size();

	// Ghosts are POWERFULL, they eat before Pacman!
	for (int i = 0; i < nb_ghosts; ++i)
	{
		if (_ghosts[i].GetPosition() == pac_pos)
		{
			_game_finished = true;
			_winning = false;
			return;
		}
	}

	// Handle Pacman eating
	if (char_under_pac == TOKEN_CHAR)
	{
		++_current_token;
		_score += TOKEN_SCORE;
		_level->SetCharAt(pac_pos, ' ');
	}
	if (_current_token == _total_token)
	{
		_game_finished = true;
		_winning = true;
		return;
	}

	// Handle Pacman moving (wall, warp, etc.)
	Vector2<int> pac_newpos = HandleMove(pac_pos, _pacman->GetDirection());
	_pacman->SetPosition(pac_newpos);

	// Handle Ghosts moving (wall, warp, etc.)
	for (int i = 0; i < nb_ghosts; ++i)
	{
		_ghosts[i].Think();

		const Vector2<int> ghost_pos = _ghosts[i].GetPosition();
		const Vector2<int> ghost_dir = _ghosts[i].GetDirection();

		Vector2<int> ghost_new_pos = HandleMove(ghost_pos, ghost_dir);
		_ghosts[i].SetPosition(ghost_new_pos);
	}
}

void Game::Draw(void) const
{
	// Clear the console
	ConsoleUtils::ClearConsole();

	if (!_game_finished)
	{
		// Draw the level first, then the rest
		_level->Draw();
		_pacman->Draw();
		const int Size = _ghosts.size();
		for (int i = 0; i < Size; ++i)
		{
			_ghosts[i].Draw();
		}

		// Draw the score at the end
		ConsoleUtils::SetCursorPosition(_level->Width() + 5, 2);
		cout << "Score : " << _score;
	}
	else
	{
		cout << "YOU " << (_winning ? "WIN!" : "LOOSE!") << endl;
		cout << "Score : " << _score << endl;
		cout << endl << endl << "Press ESC to quit." << endl;
	}
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
	if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::LEFT_ARROW))
	{
		_pacman->SetDirection(Vector2<int>(-1, 0));
	}
	else if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::RIGHT_ARROW))
	{
		_pacman->SetDirection(Vector2<int>(1, 0));
	}
	else if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::DOWN_ARROW))
	{
		_pacman->SetDirection(Vector2<int>(0, 1));
	}
	else if (KeyboardUtils::IsKeyPressed(KeyboardUtils::Keys::UP_ARROW))
	{
		_pacman->SetDirection(Vector2<int>(0, -1));
	}
}

Vector2<int> Game::FindWarpZone(const char warp_chr, const Vector2<int> &current_pos) const
{
	const int height = _level->Height();
	const int width = _level->Width();

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i == current_pos.y && j == current_pos.x)
				continue;

			char chr = _level->GetCharAt(j, i);
			if (chr == warp_chr)
				return Vector2<int>(j, i);
		}
	}
	return Vector2<int>(-1, -1);
}

Vector2<int> Game::HandleMove(const Vector2<int> &current_pos, const Vector2<int> &current_dir) const
{
	// Handle moving (wall, warp, etc.)
	Vector2<int> new_pos = current_pos + current_dir;
	if (!_level->IsInsideLevel(new_pos))
	{
		// WARP ZONE!!!
		char under_pos = _level->GetCharAt(current_pos);
		if (under_pos == ' ')
		{
			// Check at the other side of the level if there is a warp zone
			Vector2<int> other_side_pos = new_pos;
			other_side_pos.x = other_side_pos.x < 0 ? _level->Width() - other_side_pos.x : other_side_pos.x;
			other_side_pos.x = other_side_pos.x % _level->Width();
			other_side_pos.y = other_side_pos.y < 0 ? _level->Width() - other_side_pos.y : other_side_pos.y;
			other_side_pos.y = other_side_pos.y % _level->Height();
			if (_level->GetCharAt(other_side_pos) != ' ')
			{
				new_pos = current_pos;
			}
		}
		else
		{
			new_pos = FindWarpZone(under_pos, current_pos);
		}
	}
	else if (_level->GetCharAt(new_pos) == WALL_CHAR)
	{
		// You are going into a wall, so DON'T MOVE!!
		new_pos = current_pos;
	}

	return new_pos;
}