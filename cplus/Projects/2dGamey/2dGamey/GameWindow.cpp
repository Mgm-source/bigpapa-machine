#include "pch.h"
#include "GameWindow.h"
#include "GraphicsEngine/DXEngine.h"
#include "GraphicsEngine/ImageLoader.h"
#include <iostream>

GameWindow::GameWindow() : m_pvBuffer{ nullptr }, m_pvShader{ nullptr }, m_ppShader{ nullptr }, m_pcBuffer{nullptr}, Window()
{
	m_engine = DXEngine::instance();
}

GameWindow::~GameWindow()
{
	m_ppShader->release();
	m_pvBuffer->release();
	m_pvShader->release();
	m_engine->release();
	m_pcBuffer->release();
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

	{{-0.5f,  0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f,0.0f }},
	{{0.5f,  0.5f, 0.0f},  {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f,0.0f }},
	{{0.5f, -0.5f, 0.0f},  {0.5f,  -0.5f, 0.0f}, {0.0f, 0.0f,0.0f }},
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
	DXEngine::instance()->clearRenderTarget();
	DXEngine::instance()->setViewPort(m_screenWidth, m_screenHeight);

	Constant cc = {};
	cc.m_time = GetTickCount();

	m_pcBuffer->update(DXEngine::instance()->getContext(), &cc);

	DXEngine::instance()->setConstantBuffer(m_pvShader, m_pcBuffer);
	DXEngine::instance()->setConstantBuffer(m_ppShader, m_pcBuffer);
	
	DXEngine::instance()->setVertexShader(m_pvShader);
	DXEngine::instance()->setPixelShader(m_ppShader);

	DXEngine::instance()->setVertexBuffer(m_pvBuffer);

	DXEngine::instance()->drawTriangles(m_pvBuffer->length(), 0);

	DXEngine::instance()->present(0);

}