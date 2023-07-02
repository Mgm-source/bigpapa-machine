#include "pch.h"
#include "WinApp.h"
#include "AABB.h" 
#include "DXEngine.h"

winApp::winApp() : m_window{ nullptr }, m_screenWidth {1920}, m_screenHeight{1080}, m_mouse{ {0,0}, MOUSE::MouseEvents::NONE },
m_pPixelShader {nullptr}, m_pVertexBuffer {nullptr}, m_pVertexShader {nullptr}
{
}

winApp::~winApp()
{
	m_pVertexBuffer->release();
	m_pVertexShader->release();
	m_pPixelShader->release();
}

void winApp::Tick()
{
	m_timer.Tick(
		[&]() 
		{ 
			Update(m_timer.getElapsedSeconds());
		});

	Render();
}

void winApp::Update(double elapsedSeconds)
{
	if (m_mouse.isLeftButtonClicked())
	{
		double elapsedSecondsdosometing = elapsedSeconds *2;
		elapsedSecondsdosometing;
	}
}

void winApp::Render()
{
	if (!m_timer.getFrameCount())
		return;

	DXEngine::get()->clearRenderTarget();
	DXEngine::get()->setViewPort();

	DXEngine::get()->setVertexShader(m_pVertexShader);
	DXEngine::get()->setPixelShader(m_pPixelShader);


	DXEngine::get()->setVertexBuffer(m_pVertexBuffer);

	DXEngine::get()->drawTriangles(m_pVertexBuffer->length(), 0);

	DXEngine::get()->get()->m_SyncedRenderer.startDraw();
	DXEngine::get()->get()->m_SyncedRenderer.clear();
	DXEngine::get()->get()->m_SyncedRenderer.endDraw();

	DXEngine::get()->present(true);


}

void winApp::OnPaused()
{

}

void winApp::ScreenSize(UINT & width, UINT & height)
{
	width = m_screenWidth; height = m_screenHeight;
}

bool winApp::Initalise(HWND window)
{
	auto adapter = DXEngine::get()->CreateAdpater();
	DXEngine::get()->setScreenSize(m_screenWidth, m_screenHeight);
	adapter->initalise();
	DXEngine::get()->intialise(adapter, window,true);

	adapter->release();

	Vertex3 v[] =
	{
		{ -1.0f,   1.0f, 0.0f},
		{ -0.98f,  0.98f, 0.8f},
		{ -1.0f,   0.98f, 0.8f},


		{ -0.001f,   0.005f, 0.0f},
		{ -0.001f,  -0.005f, 0.0f},
		{ -0.0051f,  -0.005f, 0.0f},

		//{ 0.001f,   0.5f, 0.0f},
		//{ 0.501f,  -0.5f, 0.0f},
		//{ 0.001f,  -0.5f, 0.0f},
	};

	m_pVertexBuffer = DXEngine::get()->CreateVertexBuffer();
	
	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	DXEngine::get()->compileShader(L"VertexShader.hlsl", "vs_5_0","vertexMain",&shaderByteCode,&shaderSize);

	m_pVertexShader = DXEngine::get()->CreateVertexShader(shaderByteCode, shaderSize);

	m_pVertexBuffer->load(v, sizeof(Vertex3), static_cast<UINT>(std::size(v)), shaderByteCode, shaderSize);
	
	DXEngine::get()->releaseCompileShader();

	DXEngine::get()->compileShader(L"PixelShader.hlsl","ps_5_0", "pixelMain", &shaderByteCode, &shaderSize);

	m_pPixelShader = DXEngine::get()->CreatePixelShader(shaderByteCode, shaderSize);

	DXEngine::get()->releaseCompileShader();

	return true;
}

void winApp::OnResume()
{
}

void winApp::OnActive()
{
}

void winApp::OnMinimised()
{
}

void winApp::OnFullScreen()
{

}

void winApp::OnMouseEvent(int x, int y, MOUSE::MouseEvents event)
{
	m_mouse.position = { (float)x,(float)y };

	if (event != MOUSE::MouseEvents::NONE)
	{
		m_mouse.event |= event;
	}
}