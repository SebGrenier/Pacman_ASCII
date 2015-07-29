#pragma once
#include "Vector2.h"

class Pacman
{
public:
	Pacman(char chr);
	~Pacman(void);

	inline void SetPosition(const Vector2<int> &position) { _position = position; }
	const Vector2<int>& GetPosition(void) const { return _position; }

	void Draw(void) const;
private:
	char _character;
	Vector2<int> _position;
};