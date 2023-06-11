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


	DXEngine::get()->present(true);

	//m_pImmdiate->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::Beige);

	//// Binding render target view
	//m_pImmdiate->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	//// ViewPort 
	//m_viewPort.Width = static_cast<float>(m_screenWidth);
	//m_viewPort.Height = static_cast<float>(m_screenHeight);
	//m_viewPort.TopLeftX = 0.0f;
	//m_viewPort.TopLeftY = 0.0f;
	//m_viewPort.MinDepth = 0.0f;
	//m_viewPort.MaxDepth = 1.0f;

	//// Bind viewPort

	//m_pImmdiate->RSSetViewports(1, &m_viewPort);

	////Release the D3D 11 Device
	//m_pKeyedMutex11->ReleaseSync(0);

	////Use D3D10.1 device
	//m_pKeyedMutex10->AcquireSync(0, 5);

	////Draw D2D content        
	//m_pD2DRenderTarget->BeginDraw();

	////Clear D2D Background
	//m_pD2DRenderTarget->SetTransform(D2D1::IdentityMatrix());
	//m_pD2DRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

	//std::wstring fps = L"Frames per Secound: " + std::to_wstring(m_timer.getFramePerSecond());
	//std::wstring gameTime = L"Game running time: " + std::to_wstring((int)m_timer.getTotalSeconds());
	//std::wstring elapsedTime = L"Frame time: " + std::to_wstring(m_timer.getElapsedSeconds());
	////std::wostringstream wos;

	////Create our string
	//std::wostringstream printString;
	//printString << fps << std::endl << gameTime << std::endl << elapsedTime;
	//auto printText = printString.str();

	////Set the Font Color
	//D2D1_COLOR_F FontColor = D2D1::ColorF(0.0f, 1.0f, 1.0f, 1.0f);

	////Set the brush color D2D will use to draw with
	//m_pTextBrush->SetColor(FontColor);

	////Create the D2D Render Area
	//D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, m_screenWidth, m_screenHeight);

	////Draw the Text
	//m_pD2DRenderTarget->DrawText(
	//	printText.c_str(),
	//	wcslen(printText.c_str()),
	//	m_pTextFormat,
	//	layoutRect,
	//	m_pTextBrush
	//);

	//m_pD2DRenderTarget->EndDraw();

	////Release the D3D10.1 Device
	//m_pKeyedMutex10->ReleaseSync(1);

	////Use the D3D11 Device
	//m_pKeyedMutex11->AcquireSync(1, 5);

	////Set the blend state for D2D render target texture objects
	//m_pImmdiate->OMSetBlendState(Transparency, NULL, 0xffffffff);

	////Set the d2d vertex buffer
	//UINT stride = sizeof(Vertex);
	//UINT offset = 0;
	//m_pImmdiate->IASetVertexBuffers(0, 1, &m_pD2DVertBuffer, &stride, &offset);
	//m_pImmdiate->IASetInputLayout(m_pLayout);

	//m_pSwapChain->Present(1, 0);
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
	DXEngine::get()->intialise(adapter, window,false);

	adapter->release();

	Vertex3 v[] =
	{
		{ 0.5f,  -0.5f, 0.0f},
		{-0.5f,  -0.5f, 0.0f},
		{-0.5f,   0.5f, 0.0f}
	};

	m_pVertexBuffer = DXEngine::get()->CreateVertexBuffer();
	
	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	DXEngine::get()->compileVertexShader(L"VertexShader.hlsl","vertexMain",&shaderByteCode,&shaderSize);

	m_pVertexShader = DXEngine::get()->CreateVertexShader(shaderByteCode, shaderSize);

	m_pVertexBuffer->load(v, sizeof(Vertex3), static_cast<UINT>(std::size(v)), shaderByteCode, shaderSize);
	
	DXEngine::get()->releaseCompileShader();

	DXEngine::get()->compilePixelShader(L"PixelShader.hlsl", "pixelMain", &shaderByteCode, &shaderSize);

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