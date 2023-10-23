#pragma once
#include "WinApp.h"
#include "GraphicsEngine/DXEngine.h"

class Game : public winApp
{
	DXEngine m_engine;
public:
	Game() = default;
	~Game();
	bool initialise(HWND window);
	void OnMouseEvent(int x, int y, unsigned int state = 0);
};