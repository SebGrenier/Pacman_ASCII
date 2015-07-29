#pragma once
#include "Level.h"
#include "Pacman.h"
#include <string>

class Game
{
public:
	static const char PACMAN_CHAR = '@';
	static const char TOKEN_CHAR = '.';
	static const char GHOST_CHAR = 'g';
public:
	Game(void);
	~Game(void);

	void LoadLevel(const std::string &filename);

	void InitLevel(void);

	void ClearLevel(void);

	void Draw(void) const;

	void HandleInputs(void);

	inline bool IsRunning(void) const { return _is_running; }

private:
	bool _is_running;

	Level *_level;
	Pacman *_pacman;
};