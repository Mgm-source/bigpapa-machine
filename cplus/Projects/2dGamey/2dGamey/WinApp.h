#pragma once
#include "Timer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
class winApp
{
	// Private Member Variables
	HWND m_window;

	VertexBuffer* m_pVertexBuffer;
	VertexShader* m_pVertexShader;
	PixelShader* m_pPixelShader;

	UINT m_screenWidth;
	UINT m_screenHeight;
	
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
	winApp();
	~winApp();
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