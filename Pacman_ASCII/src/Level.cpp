#include "Level.h"
#include <fstream>
#include <iostream>

using namespace std;

Level::Level(string filename)
{
	ifstream file_io;
	file_io.open(filename.c_str());
	if (file_io.is_open())
	{
		_level_data.clear();

		string line = "";
		getline(file_io, line);
		while (!line.empty() || !file_io.eof())
		{
			if (line.empty())
				continue;

			// This is not the correct way, as we need to make sure that very line have the same dimension, but whatever...
			// TODO : trim the lines from endlines and whitespaces
			vector<char> newLine;
			string::size_type line_size = line.size();
			for (string::size_type i = 0; i < line_size; ++i)
			{
				newLine.push_back(line[i]);
			}

			_level_data.push_back(newLine);

			// Empty the line first
			line = "";
			getline(file_io, line);
		}

		_height = (int)_level_data.size();
		_width = (int)_level_data[0].size();
	}
	else
	{
		string msg = "Could not open file " + filename;
		throw exception(msg.c_str());
	}
}

Level::Level(const char * const level_data, int height, int width)
{
	throw exception("Not implemented.");
}

Level::~Level()
{
}

void Level::Draw(void) const
{
	auto it_height = _level_data.cbegin();
	auto end_height = _level_data.cend();
	for (; it_height != end_height; ++it_height)
	{
		auto it_width = it_height->cbegin();
		auto end_width = it_height->cend();
		for (; it_width != end_width; ++it_width)
		{
			cout << *it_width;
		}
		cout << endl;
	}
}
