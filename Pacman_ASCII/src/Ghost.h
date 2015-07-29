#pragma once
#include "GhostAI.h"
#include "Vector2.h"

class Ghost
{
public:
	Ghost(char chr);
	~Ghost(void);

	inline void SetPosition(const Vector2<int> &position) { _position = position; }
	const Vector2<int>& GetPosition(void) const { return _position; }

	inline void SetDirection(const Vector2<int> &direction) { _direction = direction; }
	inline const Vector2<int> GetDirection(void) const { return _direction; }

	void Draw(void) const;

	// The ghost takes ownership of the ai
	void SetAI(IGhostAI *ai);
	IGhostAI * GetAI(void) const;

	void Think(void);

private:
	char _character;
	Vector2<int> _position;
	Vector2<int> _direction;

	IGhostAI * _ghost_ai;
};