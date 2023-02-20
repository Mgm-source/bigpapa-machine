#pragma once
#include "pch.h"
#include "Timer.h"

class DXRender
{
	// Private Member Variables
	HWND m_window;

	//Direct3D Attributes
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pImmdiate;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	D3D11_VIEWPORT m_viewPort;

	size_t m_screenWidth;
	size_t m_screenHeight;
	
	MOUSE::State m_mouse;
	
	M_TMR::Timer m_timer;
private:
	// Member Functions
	void Render();
	void Draw();
	void Update(double elapsedSeconds);
	void Clear(RECT& rc);
public:		
	// Member Functions
	DXRender();
	~DXRender();
	bool Initalise(HWND window);
	void Tick();
	void ScreenSize(UINT & width, UINT & height);
	void OnPaused();
	void OnResume();
	void OnActive();
	void OnMinimised();
	void OnFullScreen();
	void OnMouseEvent(int x, int y, MOUSE::MouseEvents event = MOUSE::MouseEvents::NONE);
};

