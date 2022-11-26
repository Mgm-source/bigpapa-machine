#include "pch.h"
#include "Game.h"


Game::Game() : m_window{ nullptr }, m_screenWidth {800}, m_screenHeight{600}, m_bitmap {nullptr}
{
	m_bkgdBrush = CreateSolidBrush(RGB(255,255,255));
}

Game::~Game()
{
	DeleteObject(m_bkgdBrush);
	DeleteObject(m_bitmap.Handle);
}

bool Game::Initalise(HWND window)
{
	if (!window)
	{
		return false;
	}

	m_window = window;

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

HDC Game::Clear(RECT& rc,HDC hdc)
{	
	HDC Memdc = CreateCompatibleDC(hdc);

	if (!m_bitmap.Handle) 
	{
		m_bitmap.Handle = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		GetObjectW(m_bitmap.Handle, sizeof(BITMAP), &m_bitmap.Info);
	} 

	if (rc.right != m_bitmap.Info.bmWidth || rc.bottom != m_bitmap.Info.bmHeight)
	{
		DeleteObject(m_bitmap.Handle);
		m_bitmap.Handle = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		GetObjectW(m_bitmap.Handle, sizeof(BITMAP), &m_bitmap.Info);
	}

	SelectObject(Memdc, m_bitmap.Handle);
	FillRect(Memdc, &rc, m_bkgdBrush);

	std::wstring fps = L"Frames per Secound: " + std::to_wstring(m_timer.getFramePerSecond());
	std::wstring gameTime = L"Game running time: " + std::to_wstring((int)m_timer.getTotalSeconds());
	std::wstring elapsedTime = L"Frame time: " + std::to_wstring(m_timer.getElapsedSeconds());
	std::wostringstream wos;

	wos << L"Width: " << m_screenWidth << L", Height: " << m_screenHeight;

	TextOutW(Memdc, 0, 0, wos.str().c_str(), static_cast<int>(wos.str().size()));
	TextOutW(Memdc, (static_cast<int>(m_screenWidth) / 2), 0, fps.c_str(), static_cast<int>(fps.size()));
	TextOutW(Memdc, (static_cast<int>(m_screenWidth) / 4), 0, elapsedTime.c_str(), static_cast<int> (elapsedTime.size()));
	TextOutW(Memdc, static_cast<int>(m_screenWidth - (gameTime.size() * 7)), 0, gameTime.c_str(), static_cast<int>(gameTime.size()));

	return Memdc;
}

void Game::Update(double elapsedSeconds)
{
	elapsedSeconds;
}

void Game::Render()
{
	if (!m_timer.getFrameCount())
		return;

	RECT rc;

	GetClientRect(m_window, &rc);
	HDC hdc = GetDC(m_window);
	HDC Memdc = Clear(rc, hdc);
	
	// draw here 

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, Memdc, 0, 0, SRCCOPY);

	DeleteDC(Memdc);
	ReleaseDC(m_window, hdc);
}

void Game::OnPaused()
{
}

void Game::ScreenSize(size_t& width, size_t& height)
{
	if (width && height) // No point changing the screen size to be a 0 or just a line; retain the previous size.
	{
		m_screenWidth = width;
		m_screenHeight = height;

		return;
	}

	width = m_screenWidth;
	height = m_screenHeight;

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
