#pragma once
#include "Vector2.h"

class Pacman
{
public:
	Pacman(char chr);
	~Pacman(void);

	inline void SetPosition(const Vector2<int> &position) { _position = position; }
	const Vector2<int>& GetPosition(void) const { return _position; }

	inline void SetDirection(const Vector2<int> &direction) { _direction = direction; }
	inline const Vector2<int> GetDirection(void) const { return _direction; }

	void Draw(void) const;
private:
	char _character;
	Vector2<int> _position;
	Vector2<int> _direction;
};