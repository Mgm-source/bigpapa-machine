#include "pch.h"
#include "GameWindow.h"

int main()
{
	GameWindow game;
	if (game.init())
	{
		while (game.isRunning())
		{
			game.broadcast();
		}
	}
	return 0;
}