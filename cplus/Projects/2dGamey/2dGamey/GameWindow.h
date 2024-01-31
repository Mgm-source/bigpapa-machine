#pragma once
#include "Window.h"
#include "GraphicsEngine/DXEngine.h"

class GameWindow : public Window
{
	DXEngine* m_engine;
	VertexBuffer* m_vBuffer;
	VertexShader* m_vShader;
	PixelShader* m_pShader;

public:
	GameWindow();
	~GameWindow();
	bool init();
	void onCreate() override;
	void onUpdate() override;
};