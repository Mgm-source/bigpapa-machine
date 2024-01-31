#pragma once
#include "Window.h"
#include "GraphicsEngine/DXEngine.h"

class GameWindow : public Window
{
	 DXEngine* m_engine;
public:
	GameWindow();
	~GameWindow() = default;
	bool init();
	void onCreate() override;
	void onUpdate() override;
};