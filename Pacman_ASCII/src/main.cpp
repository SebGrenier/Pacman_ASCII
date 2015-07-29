#include "Game.h"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <time.h>

using namespace std;

int main(int argc, char** argv)
{
	// Init random seed
	srand(time(0));

	// Load the file passed as argument
	if (argc != 2)
	{
		cout << "Error, you must have exactly one argument." << endl;
	}
	string filename = argv[1];

	Game the_game;
	try
	{
		the_game.LoadLevel(filename);
		the_game.InitLevel();

		// Run the game
		while (the_game.IsRunning())
		{
			// Process key events
			the_game.HandleInputs();

			// Update state
			the_game.Update();

			// Draw
			the_game.Draw();

			// Sleep some!
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
	catch (exception err)
	{
		cout << "Error : " << err.what() << endl;
	}

	the_game.ClearLevel();

	return 0;
}