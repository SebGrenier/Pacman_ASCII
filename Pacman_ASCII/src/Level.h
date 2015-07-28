#pragma once
#include <vector>
#include <string>

class Level
{
public:
	Level(std::string filename);
	Level(const char * const level_data, int height, int width);

	~Level();

	void Draw(void) const;

private:
	Level(const Level &other) {}
	Level operator = (const Level &other) {}

	std::vector<std::vector<char> > _level_data;
	int _width;
	int _height;
};

