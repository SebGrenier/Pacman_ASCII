#pragma once
#include "Level.h"
#include "Pacman.h"

class Ghost;

class IGhostAI
{
public:
	IGhostAI(void);
	IGhostAI(Ghost * ghost);
	virtual ~IGhostAI(void);

	void SetGhost(Ghost * ghost);

	virtual void Init(const Level * const level, const Pacman * const pacman);

	virtual void Update(void) = 0;

protected:
	Ghost * _ghost;
	const Level * _level;
	const Pacman * _pacman;
};

class RandomGhostAI : public IGhostAI
{
public:
	RandomGhostAI(void);
	~RandomGhostAI(void);

	virtual void Update(void);

private:
	Vector2<int> GetNewDirection(const Vector2<int> &current_dir, const Vector2<int> &current_pos) const;

	int _chance_to_change_direction;
};