#include "GhostAI.h"
#include "Ghost.h"
#include "Vector2.h"
#include "Game.h"
#include <vector>
#include <algorithm>
#include <random>

IGhostAI::IGhostAI(void)
	: _ghost(0)
	, _level(0)
	, _pacman(0)
{}

IGhostAI::IGhostAI(Ghost * ghost)
	: _ghost(ghost)
	, _level(0)
	, _pacman(0)
{}

IGhostAI::~IGhostAI(void)
{
	_level = 0;
	_pacman = 0;
}

void IGhostAI::SetGhost(Ghost * ghost)
{
	_ghost = ghost;
}

void IGhostAI::Init(const Level * const level, const Pacman * const pacman)
{
	_level = level;
	_pacman = pacman;
}

RandomGhostAI::RandomGhostAI(void)
	: IGhostAI()
	, _chance_to_change_direction(25)
{}

RandomGhostAI::~RandomGhostAI(void)
{}

void RandomGhostAI::Update(void)
{
	if (_ghost == 0)
		return;

	const Vector2<int> current_dir = _ghost->GetDirection();
	const Vector2<int> current_pos = _ghost->GetPosition();

	// You will get a new direction if :
	// 1. You are stationary
	// 2. You will hit a wall
	// 3. You pass the X% test

	bool need_new_dir = false;
	if (current_dir.x == 0 && current_dir.y == 0)
		need_new_dir = true;
	else if (_level->GetCharAt(current_pos + current_dir) == Game::WALL_CHAR)
		need_new_dir = true;
	else if (rand() % 100 < _chance_to_change_direction)
		need_new_dir = true;

	if (need_new_dir)
	{
		_ghost->SetDirection(GetNewDirection(current_dir, current_pos));
	}
}

Vector2<int> RandomGhostAI::GetNewDirection(const Vector2<int> &current_dir, const Vector2<int> &current_pos) const
{
	std::vector<Vector2<int> > directions;
	directions.push_back(Vector2<int>(-1, 0));
	directions.push_back(Vector2<int>(1, 0));
	directions.push_back(Vector2<int>(0, -1));
	directions.push_back(Vector2<int>(0, 1));

	// Remove current from list
	std::remove(directions.begin(), directions.end(), current_dir);

	// Shuffle the list
	std::random_shuffle(directions.begin(), directions.end());

	const int Size = directions.size();
	for (int i = 0; i < Size; ++i)
	{
		if (_level->GetCharAt(current_pos + directions[i]) != Game::WALL_CHAR)
			return directions[i];
	}

	return Vector2<int>::ZERO();
}