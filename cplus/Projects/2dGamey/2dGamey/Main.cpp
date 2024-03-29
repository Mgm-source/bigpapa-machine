#include "pch.h"
#include "Game.h"
#include <limits>
#include "ImageLoader.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LPCWSTR g_pszAppName = L"SandBox";
LPCWSTR g_pszClassName = L"GameWindwow";

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) 
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    Game game;

    ImageLoader::Image spriteSheet(ImageLoader::ImageType::PNG, 320, 32, 4);
    bool worked = spriteSheet.load(R"(..\..\assets\robot.png)");
    
	{
        // Register class
        WNDCLASSEXW wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEXW);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIconW(hInstance, L"IDI_ICON");
        wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszClassName = g_pszClassName;
        wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");

        if (!RegisterClassExW(&wcex))
            return 1;

        size_t screenWidth = 0, screenHeight = 0;
        game.ScreenSize(screenWidth, screenHeight);

        RECT rc = { 0, 0, static_cast<LONG>(screenWidth), static_cast<LONG>(screenHeight) };

        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        HWND hwnd = CreateWindowExW(0, g_pszClassName, g_pszAppName, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
            nullptr, nullptr, nullptr, &game);

        if (!game.Initalise(hwnd))
            return 0;

        ShowWindow(hwnd, nCmdShow);

	}
    
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
            game.Tick();
        }
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Game* game = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CREATE:
        if (lParam)
        {
            auto params = reinterpret_cast<LPCREATESTRUCTW>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(params->lpCreateParams));
        }
        break;

    case WM_PAINT:
        if (game)
        {
            game->Tick(); // should just black out the screen and/or inform user what window event is causing the draw
        }
    break;
    case WM_ENTERSIZEMOVE:
        // Pause game here
        break;
    case WM_EXITSIZEMOVE:
        // resume game here
        break;
    case WM_SIZE:
        if (game)
        {
            size_t width = LOWORD(lParam);
            size_t height = HIWORD(lParam);
            game->ScreenSize(width, height);
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
        if (game) 
        {
            game->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;
    case WM_LBUTTONDOWN:
        if (game)
        {
            game->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),MouseEvents::LEFTDOWN);
        }
        break;
    case WM_LBUTTONUP:
        if (game)
        {
            game->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MouseEvents::LEFTUP);
        }
        break;
    case WM_RBUTTONDOWN:
        if (game)
        {
            game->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MouseEvents::RIGHTDOWN);
        }
        break;
    case WM_RBUTTONUP:
        if (game)
        {
            game->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), MouseEvents::RIGHTUP);
        }
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
