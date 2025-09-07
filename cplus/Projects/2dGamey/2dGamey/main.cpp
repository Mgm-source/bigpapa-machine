#include "pch.h"
#include "GameWindow.h"

 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	GameWindow game;

	if (game.init())
	{
		while (game.isRunning())
		{
			game.run();
		}
	}
	return 0;
}