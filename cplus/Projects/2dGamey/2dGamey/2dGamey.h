#pragma once
#include "WinApp.h"

class Game : public winApp
{
public:
	Game() = default;
	~Game() = default;
	bool initialise(HWND window);
};