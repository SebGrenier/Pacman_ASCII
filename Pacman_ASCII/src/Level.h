#pragma once
#include "Vector2.h"
#include <vector>
#include <string>

class Level
{
public:
	Level(std::string filename);
	Level(const char * const level_data, int height, int width);

	~Level();

	void Draw(void) const;

	char GetCharAt(int x, int y) const;
	void SetCharAt(int x, int y, char value);

	char GetCharAt(const Vector2<int> &pos) const;
	void SetCharAt(const Vector2<int> &pos, char value);

	inline int Height(void) const { return _height; }
	inline int Width(void) const { return _width; }

	bool IsInsideLevel(const Vector2<int> &pos) const;

private:
	Level(const Level &other) {}
	Level operator = (const Level &other) {}

	std::vector<std::vector<char> > _level_data;
	int _width;
	int _height;
};

