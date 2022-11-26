#pragma once
#include "pch.h"
#include "Timer.h"

class Game
{
	// Private Member Variables
	HWND m_window;

	struct 
	{
		HBITMAP Handle;
		BITMAP Info;
	} m_bitmap;
	
	HBRUSH m_bkgdBrush;

	size_t m_screenWidth;
	size_t m_screenHeight;

	M_TMR::Timer m_timer;
private:
	// Member Functions
	void Render();
	void Update(double elapsedSeconds);
	HDC Clear(RECT& rc, HDC hdc);
public:		
	// Member Functions
	Game();
	~Game();
	bool Initalise(HWND window);
	void Tick();
	void ScreenSize(size_t& width, size_t& height);
	void OnPaused();
	void OnResume();
	void OnActive();
	void OnMinimised();
	void OnFullScreen();
};

