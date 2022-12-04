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
	HBRUSH m_hatchedBrush;
	HPEN m_pen;
	HDC m_hdc;
	HDC m_memdc;

	size_t m_screenWidth;
	size_t m_screenHeight;

	struct 
	{
		int getX() { return position.x; };
		int getY() { return position.y; };
		struct { int x, y; } position;
		bool leftButtonDown;
		bool rightButtonDown;
	} m_mouse;
	

	M_TMR::Timer m_timer;
private:
	// Member Functions
	void Render();
	void Draw();
	void Update(double elapsedSeconds);
	void Clear(RECT& rc);
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
	void OnMouseEvent(int x, int y, MouseEvents event = MouseEvents::NONE);
};

