#include "pch.h"
#include "GameWindow.h"
#include "GraphicsEngine/DXEngine.h"
#include "GraphicsEngine/ImageLoader.h"
#include <iostream>

GameWindow::GameWindow() : m_pvBuffer{ nullptr }, m_pvShader{ nullptr }, m_ppShader{ nullptr }, m_pcBuffer{nullptr},m_timer {}, Window()
{
	m_engine = DXEngine::instance();
	m_timer.setFixedTimerStep();
}

GameWindow::~GameWindow()
{
	delete m_ppShader;
	delete m_pvBuffer;
	delete m_pvShader;
	delete m_engine;
	delete m_pcBuffer;
}

bool GameWindow::init()
{
    return Window::init();
}

void GameWindow::onCreate()
{
	//ImageLoader::Image sprite(ImageLoader::ImageType::PNG, 50, 50, 4);
	//sprite.load("test.png");

	DXEngine::instance()->intialise(nullptr, m_window,m_screenWidth,m_screenHeight);

	Vertex3 v[] = {
	{{-0.5f, -0.5f, 0.0f}, {-0.30f, -0.11f, 0.0f}, {1.0f, 0.0f,0.0f }},
	{{-0.5f,  0.5f, 0.0f}, {-0.10f, 0.70f, 0.0f}, {0.0f, 1.0f,0.0f }},
	{{0.5f,  -0.5f, 0.0f}, { 0.5f,	-0.5f, 0.0f}, {0.0f, 0.0f,1.0f }},

	{{-0.5f,  0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f,1.0f }},
	{{0.5f,  0.5f, 0.0f},  {-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f,0.0f }},
	{{0.5f, -0.5f, 0.0f},  {0.5f,  -0.5f, 0.0f}, {1.0f, 0.0f,0.0f }},
	};

	m_pvBuffer = DXEngine::instance()->CreateVertexBuffer();

	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	DXEngine::instance()->compileShader(L"Shaderfiles/VertexShader.hlsl", "vs_5_0", "vertexMain", &shaderByteCode, &shaderSize);

	m_pvShader = DXEngine::instance()->CreateVertexShader(shaderByteCode, shaderSize);

	m_pvBuffer->load(v, sizeof(Vertex3), static_cast<UINT>(std::size(v)), shaderByteCode, shaderSize);

	DXEngine::instance()->releaseCompileShader();

	DXEngine::instance()->compileShader(L"ShaderFiles/PixelShader.hlsl", "ps_5_0", "pixelMain", &shaderByteCode, &shaderSize);

	m_ppShader = DXEngine::instance()->CreatePixelShader(shaderByteCode, shaderSize);

	DXEngine::instance()->releaseCompileShader();

	Constant cc = {0};

	m_pcBuffer = DXEngine::instance()->CreateConstantBuffer();

	m_pcBuffer->load(&cc,sizeof(Constant));
}

void GameWindow::onUpdate()
{
	m_timer.Tick([&]() {
		update(m_timer.getElapsedSeconds());
	});

	render();
}

void GameWindow::update(double elapsedseconds)
{
	Constant cc = {};
	cc.m_time = m_timer.getTotalTicks() / 1000;
	cc.m_world.setTraslation(DirectX::XMFLOAT3(((m_screenWidth - m_mouse.getX() * 2 ) / (m_screenWidth)) / -1, ((m_screenHeight - m_mouse.getY() * 2) / (m_screenHeight)), 1));
	cc.m_view.setIdentity();
	cc.m_screen.setOrthogonal(DirectX::XMFLOAT4(m_screenWidth / 400.0f, m_screenHeight / 400.0f, -4.0f, 4.0f));
	m_pcBuffer->update(DXEngine::instance()->getContext(), &cc);
}

void GameWindow::render()
{
	DXEngine::instance()->clearRenderTarget();
	DXEngine::instance()->setViewPort(m_screenWidth, m_screenHeight);

	DXEngine::instance()->setConstantBuffer(m_pvShader, m_pcBuffer);
	DXEngine::instance()->setConstantBuffer(m_ppShader, m_pcBuffer);

	DXEngine::instance()->setVertexShader(m_pvShader);
	DXEngine::instance()->setPixelShader(m_ppShader);

	DXEngine::instance()->setVertexBuffer(m_pvBuffer);

	DXEngine::instance()->drawTriangles(m_pvBuffer->length(), 0);

	DXEngine::instance()->present(0);
}
