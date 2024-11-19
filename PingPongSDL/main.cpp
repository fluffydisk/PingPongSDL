#include "Game.h"
#include <iostream>


int main(int argc, char* argv[])
{
	Game game;

	while ( !game.GameEnd() )
	{
		game.Update();
	}
	return 0;
}