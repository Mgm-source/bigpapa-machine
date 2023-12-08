#include "pch.h"
#include "2dGamey.h"
#include "GraphicsEngine/DXEngine.h"

bool Game::initialise(HWND window)
{
    m_engine.intialise(nullptr, window);
    return true;
}

void Game::OnMouseEvent(int x, int y, unsigned int state)
{
    winApp::OnMouseEvent(x, y, state);
}

void Game::handleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        Run();//App->Tick(); // should just black out the screen and/or inform user what window event is causing the draw
        break;
    }
    case WM_ENTERSIZEMOVE:
        // Pause app here
        break;
    case WM_EXITSIZEMOVE:
        // resume app here
        break;
    case WM_SIZE:
    {
        UINT width = LOWORD(lParam);
        UINT height = HIWORD(lParam);
        setWindowSize(width, height);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_GETMINMAXINFO:
        if (lParam)
        {
            MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMinTrackSize.x = 320;
            info->ptMinTrackSize.y = 200;
        }
        break;
    case WM_MOUSEMOVE:
        OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_LBUTTONDOWN:
        OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MOUSE::MouseEvents::LEFTDOWN);
        break;
    case WM_LBUTTONUP:
        OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MOUSE::MouseEvents::LEFTUP);
        break;
    case WM_RBUTTONDOWN:
        OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MOUSE::MouseEvents::RIGHTDOWN);
        break;
    case WM_RBUTTONUP:
        OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MOUSE::MouseEvents::RIGHTUP);
        break;
    }
}

void Game::Run()
{
    m_engine.clearRenderTarget();
    m_engine.present(0);
}

bool Game::start()
{
    winApp::start();

    // Main message loo
    MSG msg = {};

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Run();
        }
    }

    return true;
}

int main()
{
    Game game;
    game.start();
}