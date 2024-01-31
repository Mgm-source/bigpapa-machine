#include "pch.h"
#include "GameWindow.h"
#include "GraphicsEngine/DXEngine.h"
#include <iostream>

GameWindow::GameWindow() : Window(), m_engine{ DXEngine::get() }
{

}

bool GameWindow::init()
{
    return Window::init();
}

void GameWindow::onCreate()
{
    m_engine->intialise(nullptr, m_window);
}

void GameWindow::onUpdate()
{
    m_engine->clearRenderTarget();
    m_engine->present(0);

    if (m_mouse.isLeftButtonDown())
    {
        if (DXEngine::get() == m_engine)
        {
            std::cout << "Same thing" << std::endl;
        }

    }

}