#include "pch.h"
#include "GameWindow.h"
#include "GraphicsEngine/DXEngine.h"
#include "GraphicsEngine/ImageLoader.h"
#include <iostream>
#include <GraphicsEngine\ResourceFactory.h>

GameWindow::GameWindow() : m_pvBuffer{ nullptr }, m_pvShader{ nullptr }, m_ppShader{ nullptr },
m_pcBuffer{ nullptr }, m_piBuffer{ nullptr }, m_pTexture{nullptr}, m_timer {}, Window(L"GameWindow", L"2dGamey")
{
	m_engine = new DXEngine;
	m_timer.setFixedTimerStep();
	setWindowSize(800, 800);
}

GameWindow::~GameWindow()
{
	m_engine->getContext()->ClearState();
	delete m_ppShader;
	delete m_pvBuffer;
	delete m_pvShader;
	delete m_engine;
	delete m_pcBuffer;
	delete m_piBuffer;
	delete m_pTexture;
}

bool GameWindow::init()
{
    return Window::init();
}

void GameWindow::onCreate()
{

	m_engine->intialise(nullptr, m_window,m_screenWidth,m_screenHeight);

	UINT numQ = 0;
	
	m_engine->getDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, 4, &numQ);

	Vertex3 v[] = {
	{{-0.05f,  0.05f, 0.0f}, {0.0f, 0.0f, 0.0f}},
	{{0.05f,  -0.05f, 0.0f}, {1.0f, 1.0f, 0.0f}},
	{{-0.05f, -0.05f, 0.0f}, {0.0f, 1.0f, 0.0f}},
	{{-0.05f,  0.05f, 0.0f}, {0.0f, 0.0f, 0.0f}},
	{{0.05f,   0.05f, 0.0f}, {1.0f, 0.0f, 0.0f}},
	{{0.05f,  -0.05f, 0.0f}, {1.0f, 1.0f, 0.0f}},
	};

	ResourceFactory rf = ResourceFactory(m_engine->getDevice());

	m_pvBuffer = rf.CreateVertexBuffer();

	m_piBuffer = rf.CreateIndexBuffer();

	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	m_engine->compileShader(L"Shaderfiles/VertexShader.hlsl", "vs_5_0", "vertexMain", &shaderByteCode, &shaderSize);

	m_pvShader = rf.CreateVertexShader(shaderByteCode, shaderSize);

	m_pvBuffer->load(v, sizeof(Vertex3), static_cast<UINT>(std::size(v)), shaderByteCode, shaderSize);

	m_engine->releaseCompileShader();

	m_engine->compileShader(L"ShaderFiles/PixelShader.hlsl", "ps_5_0", "pixelMain", &shaderByteCode, &shaderSize);

	m_ppShader = rf.CreatePixelShader(shaderByteCode, shaderSize);

	m_engine->releaseCompileShader();

	Constant cc = {0};

	m_pcBuffer = rf.CreateConstantBuffer();

	m_pcBuffer->load(&cc,sizeof(Constant));

	cc.m_world.setTraslation(DirectX::XMFLOAT3(-0.95f,0.95f,0));
	cc.m_view.setIdentity();
	cc.m_screen.setOrthogonal(DirectX::XMFLOAT4(2, 2, -2.0f, 2.0f));
	m_pcBuffer->update(&cc,m_engine->getContext());

	ImageLoader::Image sprite;
	m_pTexture = rf.CreateTexure();
	
	sprite.load("test.png", ImageLoader::ImageType::PNG, 4);
	m_pTexture->addImage(sprite);
}

void GameWindow::run()
{
	pumpEvents();
	tickFrame();
}

void GameWindow::tickFrame()
{
	
	m_timer.Tick([&]() {
		update(m_timer.getElapsedSeconds());
		render();
	});

}

void GameWindow::update(double elapsedseconds)
{
	static float zoom = 1; // implement a camera class instead of having a static variable. 

	if (m_mouse.isWheelUp())
	{
		zoom +=10;
		m_logger.log(L"mouse up", Severity::INFO);
	}

	if (m_mouse.isWheelDown())
	{
		if (zoom == 0)
		{
			zoom =  0.1f;
		}
		zoom -= 10;
		m_logger.log(L"mouse down", Severity::INFO);
	}

	//m_logger.log(std::to_wstring(cc.m_world.matrix4x4[3][0]) + L"," + std::to_wstring(cc.m_world.matrix4x4[3][1]), Severity::INFO);
	//m_logger.log(std::to_wstring(cc.m_screen.matrix4x4[0][0]) + L"," + std::to_wstring(cc.m_screen.matrix4x4[1][1]), Severity::INFO);
}

void GameWindow::render()
{
	m_engine->clearRenderTarget();
	m_engine->setViewPort(m_screenWidth, m_screenHeight);

	m_engine->setConstantBuffer(m_pvShader, m_pcBuffer);
	m_engine->setConstantBuffer(m_ppShader, m_pcBuffer);

	m_engine->setVertexShader(m_pvShader);
	m_engine->setPixelShader(m_ppShader);

	m_pTexture->update(m_engine->getContext());

	m_engine->setVertexBuffer(m_pvBuffer);

	m_engine->drawTriangles(m_pvBuffer->length(), 0);

	m_engine->present(false);
}