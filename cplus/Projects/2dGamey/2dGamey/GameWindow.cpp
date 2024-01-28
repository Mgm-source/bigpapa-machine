#include "pch.h"
#include "GameWindow.h"
#include "GraphicsEngine/DXEngine.h"
#include <iostream>

GameWindow::GameWindow() : m_engine {}, Window()
{
   
}

bool GameWindow::init()
{
    return Window::init();
}

void GameWindow::onCreate()
{
    m_engine.intialise(nullptr, m_window);
}

void GameWindow::onUpdate()
{
    m_engine.clearRenderTarget();
    m_engine.present(0);

    if (m_mouse.isLeftButtonDown())
    {
        std::cout << "screen resolution:" << m_screenHeight << "," << m_screenWidth << std::endl;
        std::cout << "mouse position:" << m_mouse.getX() << "," << m_mouse.getY() << std::endl;
    }
}