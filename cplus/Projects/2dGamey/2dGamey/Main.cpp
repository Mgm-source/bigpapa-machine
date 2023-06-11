#include "pch.h"
#include "WinApp.h"
#include "ImageLoader.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LPCWSTR g_pszAppName = L"SandBox";
LPCWSTR g_pszClassName = L"GameWindwow";

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) 
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    winApp App;
    
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

        auto screenWidth = 0u, screenHeight = 0u;
        App.ScreenSize(screenWidth, screenHeight);

        RECT rc = { 0, 0, static_cast<LONG>(screenWidth), static_cast<LONG>(screenHeight) };

        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        HWND hwnd = CreateWindowExW(0, g_pszClassName, g_pszAppName, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
            nullptr, nullptr, nullptr, &App);

       if(!App.Initalise(hwnd))
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
            App.Tick();
        }
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    winApp* App = reinterpret_cast<winApp*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

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
        if (App)
        {
            App->Tick(); // should just black out the screen and/or inform user what window event is causing the draw
        }
    break;
    case WM_ENTERSIZEMOVE:
        // Pause game here
        break;
    case WM_EXITSIZEMOVE:
        // resume game here
        break;
    case WM_SIZE:
        if (App)
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            App->ScreenSize(width, height);
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
        if (App) 
        {
            App->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        break;
    case WM_LBUTTONDOWN:
        if (App)
        {
            App->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),MOUSE::MouseEvents::LEFTDOWN);
        }
        break;
    case WM_LBUTTONUP:
        if (App)
        {
            App->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),MOUSE::MouseEvents::LEFTUP);
        }
        break;
    case WM_RBUTTONDOWN:
        if (App)
        {
            App->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),MOUSE::MouseEvents::RIGHTDOWN);
        }
        break;
    case WM_RBUTTONUP:
        if (App)
        {
            App->OnMouseEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),MOUSE::MouseEvents::RIGHTUP);
        }
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}