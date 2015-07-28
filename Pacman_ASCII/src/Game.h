#pragma once
#include "Level.h"
#include <string>

class Game
{
public:
	Game(void);
	~Game(void);

	void LoadLevel(const std::string &filename);

	void ClearLevel(void);

	void Draw(void) const;

private:
	Level *_level;
};