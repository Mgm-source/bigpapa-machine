#include "pch.h"
#include "GameWindow.h"
#include "GraphicsEngine/DXEngine.h"
#include <iostream>

GameWindow::GameWindow() : m_engine{ DXEngine::get() }, m_vBuffer{}, m_vShader{}, m_pShader{}, Window()
{

}

GameWindow::~GameWindow()
{
	m_pShader->release();
	m_vBuffer->release();
	m_vShader->release();
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