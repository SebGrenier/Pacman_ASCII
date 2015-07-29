#pragma once
#include "Level.h"
#include "Pacman.h"
#include "Ghost.h"
#include <string>

class Game
{
public:
	static const char PACMAN_CHAR = '@';
	static const char TOKEN_CHAR = '.';
	static const char GHOST_CHAR = 'g';
	static const char WALL_CHAR = '#';
	static const int TOKEN_SCORE = 100;
public:
	Game(void);
	~Game(void);

	void LoadLevel(const std::string &filename);

	void InitLevel(void);

	void ClearLevel(void);

	void Update(void);

	void Draw(void) const;

	void HandleInputs(void);

	inline bool IsRunning(void) const { return _is_running; }

private:
	Vector2<int> HandleMove(const Vector2<int> &current_pos, const Vector2<int> &current_dir) const;
	Vector2<int> FindWarpZone(const char warp_chr, const Vector2<int> &current_pos) const;

	bool _is_running;
	bool _game_finished;
	bool _winning;
	int _score;
	int _total_token;
	int _current_token;

	Level *_level;
	Pacman *_pacman;
	std::vector<Ghost> _ghosts;
};