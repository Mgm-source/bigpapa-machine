#include "pch.h"
#include "Game.h"
#include "AABB.h" 


Game::Game() : m_window{ nullptr }, m_screenWidth {800}, m_screenHeight{600}, m_bitmap {nullptr}
{
	m_bkgdBrush = CreateSolidBrush(RGB(255,255,255));
	m_pen = CreatePen(PS_SOLID, 0, RGB(0,0,255));
	m_hatchedBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(135, 0, 0));
}

Game::~Game()
{
	DeleteObject(m_bkgdBrush);
	DeleteObject(m_bitmap.Handle);
	DeleteObject(m_pen);
	DeleteObject(m_hatchedBrush);
	DeleteDC(m_memdc);
	ReleaseDC(m_window, m_hdc);
}

bool Game::Initalise(HWND window)
{
	if (!window)
	{
		return false;
	}

	m_window = window;

	m_hdc = GetDC(m_window);
	m_memdc = CreateCompatibleDC(m_hdc);
	SetBkMode(m_memdc, TRANSPARENT);
	SelectObject(m_memdc, m_pen);
	SelectObject(m_memdc, m_hatchedBrush);

	if (!m_bitmap.Handle)
	{
		m_bitmap.Handle = CreateCompatibleBitmap(m_hdc, m_screenWidth, m_screenHeight);
		GetObjectW(m_bitmap.Handle, sizeof(BITMAP), &m_bitmap.Info);
		SelectObject(m_memdc, m_bitmap.Handle);
	}

	return true;
}

void Game::Tick()
{
	m_timer.Tick(
		[&]() 
		{ 
			Update(m_timer.getElapsedSeconds());
		});

	Render();

}

void Game::Clear(RECT& rc)
{	

	FillRect(m_memdc, &rc, m_bkgdBrush);
}

void Game::Update(double elapsedSeconds)
{
	if (m_mouse.leftButtonDown)
	{
		double elapsedSecondsdosometing = elapsedSeconds *2;
		elapsedSecondsdosometing;
	}
	;
}

void Game::Render()
{
	if (!m_timer.getFrameCount())
		return;

	RECT rc;
	GetClientRect(m_window, &rc);

	Clear(rc);
	
	Draw();

	std::wstring fps = L"Frames per Secound: " + std::to_wstring(m_timer.getFramePerSecond());
	std::wstring gameTime = L"Game running time: " + std::to_wstring((int)m_timer.getTotalSeconds());
	std::wstring elapsedTime = L"Frame time: " + std::to_wstring(m_timer.getElapsedSeconds());
	std::wostringstream wos;

	wos << L"Width: " << m_screenWidth << L", Height: " << m_screenHeight;

	TextOutW(m_memdc, 0, 0, wos.str().c_str(), static_cast<int>(wos.str().size()));
	TextOutW(m_memdc, (static_cast<int>(m_screenWidth) / 2), 0, fps.c_str(), static_cast<int>(fps.size()));
	TextOutW(m_memdc, (static_cast<int>(m_screenWidth) / 4), 0, elapsedTime.c_str(), static_cast<int> (elapsedTime.size()));
	TextOutW(m_memdc, static_cast<int>(m_screenWidth - (gameTime.size() * 7)), 0, gameTime.c_str(), static_cast<int>(gameTime.size()));

	BitBlt(m_hdc, 0, 0, rc.right, rc.bottom, m_memdc, 0, 0, SRCCOPY);
}

void Game::Draw()
{

	AABB box({ 0.0f + m_mouse.getX() ,m_mouse.getY() + 0.0f,100.0f + m_mouse.getX() , 125.0f + m_mouse.getY() });
	AABB box2({ 300.0f,200.0f,600.0f, 405.0f });

	if (box.isBoxColliding(box, box2))
	{
		HPEN aPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
		HGDIOBJ oldPen = SelectObject(m_memdc, aPen);
		Rectangle(m_memdc, box.left(), box.top(), box.right(), box.bottom());
		SelectObject(m_memdc, oldPen);
		DeleteObject(aPen);
	}
	else 
	{
		Rectangle(m_memdc, box.left(), box.top(), box.right(), box.bottom());
	}

	if (box2.isPointInside({ m_mouse.getX() + 0.0f, m_mouse.getY() + 0.0f }, box2))
	{
		HPEN aPen = CreatePen(PS_SOLID, 0, RGB(0, 255, 255));
		HGDIOBJ oldPen = SelectObject(m_memdc, aPen);
		Rectangle(m_memdc, box2.left(), box2.top(), box2.right(), box2.bottom());
		SelectObject(m_memdc, oldPen);
		DeleteObject(aPen);
	}
	else
	{
		Rectangle(m_memdc, box2.left(), box2.top(), box2.right(), box2.bottom());
	}
}

void Game::OnPaused()
{

}

void Game::ScreenSize(size_t& width, size_t& height)
{
	if (!width || !height) // No point changing the screen size to be a 0 or just a line; retain the previous size.

	{
		width = m_screenWidth;
		height = m_screenHeight;
		return;
	}
		
	if (width != m_screenWidth || height != m_screenHeight) // No point changing the screen size to be a 0 or just a line; retain the previous size.
	{

		DeleteObject(m_bitmap.Handle);
		m_bitmap.Handle = CreateCompatibleBitmap(m_hdc, width, height);
		GetObjectW(m_bitmap.Handle, sizeof(BITMAP), &m_bitmap.Info);
		SelectObject(m_memdc, m_bitmap.Handle);

		m_screenWidth = width;
		m_screenHeight = height;
	}
}

void Game::OnResume()
{
}

void Game::OnActive()
{
}

void Game::OnMinimised()
{
}

void Game::OnFullScreen()
{

}

void Game::OnMouseEvent(int x, int y, MouseEvents event)
{
	m_mouse.position = { x,y };

	switch (event)
	{
	case MouseEvents::LEFTDOWN:
		m_mouse.leftButtonDown = true;
		break;
	case MouseEvents::LEFTUP:
		m_mouse.leftButtonDown = false;
		break;
	case MouseEvents::RIGHTDOWN:
		m_mouse.rightButtonDown = true;
		break;
	case MouseEvents::RIGHTUP:
		m_mouse.rightButtonDown = false;
		break;
	}
}