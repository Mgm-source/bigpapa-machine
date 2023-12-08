#pragma once
#include "WinApp.h"
#include "GraphicsEngine/DXEngine.h"

class Game : public winApp
{
	DXEngine m_engine;
public:
	Game() = default;
	bool initialise(HWND window);
	void OnMouseEvent(int x, int y, unsigned int state = 0);
	void handleMessage(UINT message, WPARAM wParam, LPARAM lParam) override;
	void Run() override;
};