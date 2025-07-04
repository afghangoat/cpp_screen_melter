//Make sure to add -D_UNICODE -DUNICODE flags
//example build script:
//g++ -o main.exe main.cpp -lgdi32 -luser32 -D_UNICODE -DUNICODE flags
#include <Windows.h>

int ScreenWidth, ScreenHeight;
int Interval = 100;

//Offsets a chunk of pixels with some positive y offset within a random interval
LRESULT CALLBACK Melter(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_CREATE:
    {
        HDC Desktop = GetDC(HWND_DESKTOP);
        HDC Window = GetDC(hWnd);

        BitBlt(Window, 0, 0, ScreenWidth, ScreenHeight, Desktop, 0, 0, SRCCOPY);
        ReleaseDC(hWnd, Window);
        ReleaseDC(HWND_DESKTOP, Desktop);

        SetTimer(hWnd, 0, Interval, 0);
        ShowWindow(hWnd, SW_SHOW);
        break;
    }
    case WM_PAINT:
    {
        ValidateRect(hWnd, 0);
        break;
    }
    case WM_TIMER:
    {
        HDC Window = GetDC(hWnd);
        int X = (rand() % ScreenWidth) - (150 / 2),
            Y = (rand() % 15),
            Width = (rand() % 150);
        BitBlt(Window, X, Y, Width, ScreenHeight, Window, X, 0, SRCCOPY);
        ReleaseDC(hWnd, Window);
        break;
    }
    case WM_DESTROY:
    {
        KillTimer(hWnd, 0);
        PostQuitMessage(0);
        break;
    }
    return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

//The main function, Registers the melter function
int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE Prev, LPSTR Cmd, int showcmd)
{
    ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    WNDCLASS wndClass = { 0, Melter, 0,0, Inst, 0, LoadCursorW(0, IDC_ARROW), 0, 0, L"ScreenMelter" };

    if (RegisterClass(&wndClass))
    {
        HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelter", 0, WS_POPUP,
            0, 0, ScreenWidth, ScreenHeight, HWND_DESKTOP, 0, Inst, 0);
        if (hWnd)
        {
            srand(GetTickCount());
            MSG Msg = { 0 };
            while (Msg.message != WM_QUIT)
            {
                if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&Msg);
                    DispatchMessage(&Msg);
                }
            }
        }
    }
    return 0;
}