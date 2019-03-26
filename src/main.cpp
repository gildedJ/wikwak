#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine,
                    int nCmdShow)
{
  const wchar_t CLASS_NAME[] = L"Hope Window Class";

  WNDCLASS windowClass      = {};
  windowClass.lpfnWndProc   = WindowProc;
  windowClass.hInstance     = hInstance;
  windowClass.lpszClassName = CLASS_NAME;

  RegisterClass(&windowClass);

  HWND hwnd = CreateWindowEx(0,                             // Window Styles
                             CLASS_NAME,                    // Window Class
                             L"Hope Engine",                // Window Title
                             WS_OVERLAPPEDWINDOW,           // Window Style
                             CW_USEDEFAULT, CW_USEDEFAULT,  // Position
                             CW_USEDEFAULT, CW_USEDEFAULT,  // Size
                             NULL,                          // Parent Window
                             NULL,                          // Menu
                             hInstance,                     // Instance
                             NULL  // Additional App Data
  );

  if (hwnd == NULL)
  {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC         hdc = BeginPaint(hwnd, &ps);
      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
      EndPaint(hwnd, &ps);
    }
      return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}