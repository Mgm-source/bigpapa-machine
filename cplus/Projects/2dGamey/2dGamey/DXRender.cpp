#include "pch.h"
#include "DXRender.h"
#include "AABB.h" 


DXRender::DXRender() : m_window{ nullptr }, m_screenWidth {800}, m_screenHeight{600}
, m_DriverType{}
, m_FeatureLevel{}
, m_pDevice{nullptr }
, m_pImmdiate{nullptr}
, m_pRenderTargetView{nullptr}
, m_pSwapChain{nullptr}
, m_viewPort{}
, m_mouse{ {0,0}, MOUSE::MouseEvents::NONE }
{
	//m_bkgdBrush = CreateSolidBrush(RGB(255,255,255));
	//m_pen = CreatePen(PS_SOLID, 0, RGB(0,0,255));
	//m_hatchedBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(135, 0, 0));
}

DXRender::~DXRender()
{
	//DeleteObject(m_bkgdBrush);
	//DeleteObject(m_bitmap.Handle);
	//DeleteObject(m_pen);
	//DeleteObject(m_hatchedBrush);
	//DeleteDC(m_memdc);
	//ReleaseDC(m_window, m_hdc);

	if (m_pImmdiate) m_pImmdiate->ClearState();

	SafeMemory::Release(m_pRenderTargetView);
	SafeMemory::Release(m_pSwapChain);
	SafeMemory::Release(m_pImmdiate);
	SafeMemory::Release(m_pDevice);
}

bool DXRender::Initalise(HWND window)
{
	if (!window)
	{
		return false;
	}

	m_window = window;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG 
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	D3D_DRIVER_TYPE driverTypes[]
	{
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE
	,	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_WARP
	,	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes =  static_cast<UINT>(std::size(driverTypes));

	D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
	,	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1
	,	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0
	};

	UINT numFeatureLevel = static_cast<UINT>(std::size(featureLevels));

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1; 
	swapChainDesc.BufferDesc.Width = m_screenWidth;
	swapChainDesc.BufferDesc.Height = m_screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_window;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT result;
	for (size_t i = 0; i < numDriverTypes; i++)
	{
		result = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, createDeviceFlags,
			featureLevels, numFeatureLevel, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &m_FeatureLevel, &m_pImmdiate);

		if (SUCCEEDED(result))
		{
			m_DriverType = driverTypes[i];
			break;
		}
		else 
		{
			// logger
			return false;
		}
	}

	// Create render targe view

	ID3D11Texture2D* backBufferTexture = 0;

	m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBufferTexture));

	m_pDevice->CreateRenderTargetView(backBufferTexture, nullptr, &m_pRenderTargetView);

	// Binding render target view

	m_pImmdiate->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	// ViewPort 
	m_viewPort.Width = static_cast<float>(m_screenWidth);
	m_viewPort.Height = static_cast<float>(m_screenHeight);
	m_viewPort.TopLeftX = 0.0f;
	m_viewPort.TopLeftY = 0.0f;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;

	// Bind viewPort

	m_pImmdiate->RSSetViewports(1, &m_viewPort);


	//m_hdc = GetDC(m_window);
	//m_memdc = CreateCompatibleDC(m_hdc);
	//SetBkMode(m_memdc, TRANSPARENT);
	//SelectObject(m_memdc, m_pen);
	//SelectObject(m_memdc, m_hatchedBrush);

	//if (!m_bitmap.Handle)
	//{
	//	m_bitmap.Handle = CreateCompatibleBitmap(m_hdc, m_screenWidth, m_screenHeight);
	//	GetObjectW(m_bitmap.Handle, sizeof(BITMAP), &m_bitmap.Info);
	//	SelectObject(m_memdc, m_bitmap.Handle);
	//}

	//ImageLoader::Image spriteSheet(ImageLoader::ImageType::PNG, 320, 32, 4);
	//bool worked = spriteSheet.load(R"(..\..\assets\robot.png)");

	return true;
}

void DXRender::Tick()
{
	m_timer.Tick(
		[&]() 
		{ 
			Update(m_timer.getElapsedSeconds());
		});

	Render();
}

void DXRender::Clear(RECT& rc)
{	

	//FillRect(m_memdc, &rc, m_bkgdBrush);
}

void DXRender::Update(double elapsedSeconds)
{
	if (m_mouse.isLeftButtonClicked())
	{
		double elapsedSecondsdosometing = elapsedSeconds *2;
		elapsedSecondsdosometing;
	}
}

void DXRender::Render()
{
	if (!m_timer.getFrameCount())
		return;

	m_pImmdiate->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::Beige);
	m_pSwapChain->Present(0, 0);

	//RECT rc;
	//GetClientRect(m_window, &rc);

	//Clear(rc);
	//
	//Draw();

	//std::wstring fps = L"Frames per Secound: " + std::to_wstring(m_timer.getFramePerSecond());
	//std::wstring gameTime = L"Game running time: " + std::to_wstring((int)m_timer.getTotalSeconds());
	//std::wstring elapsedTime = L"Frame time: " + std::to_wstring(m_timer.getElapsedSeconds());
	//std::wostringstream wos;

	//wos << L"Width: " << m_screenWidth << L", Height: " << m_screenHeight;

	//TextOutW(m_memdc, 0, 0, wos.str().c_str(), static_cast<int>(wos.str().size()));
	//TextOutW(m_memdc, (static_cast<int>(m_screenWidth) / 2), 0, fps.c_str(), static_cast<int>(fps.size()));
	//TextOutW(m_memdc, (static_cast<int>(m_screenWidth) / 4), 0, elapsedTime.c_str(), static_cast<int> (elapsedTime.size()));
	//TextOutW(m_memdc, static_cast<int>(m_screenWidth - (gameTime.size() * 7)), 0, gameTime.c_str(), static_cast<int>(gameTime.size()));

	//BitBlt(m_hdc, 0, 0, rc.right, rc.bottom, m_memdc, 0, 0, SRCCOPY);
}

void DXRender::Draw()
{

	//AABB box({ 0.0f + m_mouse.getX() ,m_mouse.getY() + 0.0f,100.0f + m_mouse.getX() , 125.0f + m_mouse.getY() });
	//AABB box2({ 300.0f,200.0f,600.0f, 405.0f });

	//if (box.isBoxColliding(box, box2))
	//{
	//	HPEN aPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
	//	HGDIOBJ oldPen = SelectObject(m_memdc, aPen);
	//	Rectangle(m_memdc, box.left(), box.top(), box.right(), box.bottom());
	//	SelectObject(m_memdc, oldPen);
	//	DeleteObject(aPen);
	//}
	//else 
	//{
	//	Rectangle(m_memdc, box.left(), box.top(), box.right(), box.bottom());
	//}

	//if (box2.isPointInside({ m_mouse.getX() + 0.0f, m_mouse.getY() + 0.0f }, box2))
	//{
	//	HPEN aPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 255));
	//	HGDIOBJ oldPen = SelectObject(m_memdc, aPen);
	//	Rectangle(m_memdc, box2.left(), box2.top(), box2.right(), box2.bottom());
	//	SelectObject(m_memdc, oldPen);
	//	DeleteObject(aPen);
	//}
	//else
	//{
	//	Rectangle(m_memdc, box2.left(), box2.top(), box2.right(), box2.bottom());
	//}
}

void DXRender::OnPaused()
{

}

void DXRender::ScreenSize(UINT & width, UINT & height)
{
	//if (!width || !height) // No point changing the screen size to be a 0 or just a line; retain the previous size.

	//{
	//	width = m_screenWidth;
	//	height = m_screenHeight;
	//	return;
	//}
	//	
	//if (width != m_screenWidth || height != m_screenHeight) // No point changing the screen size to be a 0 or just a line; retain the previous size.
	//{

	//	DeleteObject(m_bitmap.Handle);
	//	m_bitmap.Handle = CreateCompatibleBitmap(m_hdc, width, height);
	//	GetObjectW(m_bitmap.Handle, sizeof(BITMAP), &m_bitmap.Info);
	//	SelectObject(m_memdc, m_bitmap.Handle);

	//	m_screenWidth = width;
	//	m_screenHeight = height;
	//}
}

void DXRender::OnResume()
{
}

void DXRender::OnActive()
{
}

void DXRender::OnMinimised()
{
}

void DXRender::OnFullScreen()
{

}

void DXRender::OnMouseEvent(int x, int y, MOUSE::MouseEvents event)
{
	m_mouse.position = { (float)x,(float)y };

	if (event != MOUSE::MouseEvents::NONE)
	{
		m_mouse.event |= event ;
	}
}