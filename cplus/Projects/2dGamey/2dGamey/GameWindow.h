#pragma once
#include "Window.h"
#include "GraphicsEngine/DXEngine.h"
#include "Timer.h"

class GameWindow : public Window
{
	DXEngine* m_engine;
	VertexBuffer* m_pvBuffer;
	VertexShader* m_pvShader;
	PixelShader* m_ppShader;
	ConstantBuffer* m_pcBuffer;
	M_TMR::Timer m_timer;

public:
	GameWindow();
	~GameWindow();
	bool init();
	void onCreate() override;
	void onUpdate() override;
};

void update();