#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Windows.h>

#define __cui_windows_window_include__

#include "include/window.h"
#include "include/opengl.h"

#include <glad/glad.h>

HWND hwnd;
MSG msg;

bool windowCreated = false;

// Win32 window procedure
LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  switch (msg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProcW(hwnd, msg, wparam, lparam);
  }

  return 0;
}

// Creates a new Win32 window
void cui_win32_window_new(unsigned int width, unsigned int height, const char *title) {
  if (!windowCreated) {
    windowCreated = true;

    cui_win32_opengl_init();

    // Window class
    WNDCLASSW wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = CreateSolidBrush(RGB(220, 220, 220));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpfnWndProc = wndproc;
    wc.lpszClassName = L"window"; // TODO: salt this for security
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    if (!RegisterClassW(&wc)) {
      printf("Error: Failed to register a Win32 window class.\n");
      exit(1);
    }

    int charsNum = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
    wchar_t *newTitle = malloc(charsNum);
    MultiByteToWideChar(CP_UTF8, 0, title, -1, newTitle, charsNum);    

    // Create the window
    hwnd = CreateWindowExW(
      WS_EX_CLIENTEDGE,
      wc.lpszClassName,
      newTitle,
      WS_VISIBLE | WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      width,
      height,
      NULL,
      NULL,
      wc.hInstance,
      NULL
    );

    if (!hwnd) {
      printf("Error: Failed to create a Win32 window.\n");
      exit(1);   
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    cui_win32_opengl_context();
  }
}

// Runs the Win32 window
void cui_win32_window_update() {
  TranslateMessage(&msg);
  DispatchMessageW(&msg);
  cui_win32_opengl_present();
}

// Returns a boolean value determining if the window should stay open
int cui_win32_window_active() {
  return GetMessageW(&msg, NULL, 0, 0) > 0;
}

// Closes the Win32 window
void cui_win32_window_close() {
  if (windowCreated && hwnd) {
    windowCreated = false;
    DestroyWindow(hwnd);
  }
}

// Gets the size of the Win32 window
int *cui_win32_window_getSize() {
  int *size = malloc(2 * sizeof(int));

  RECT rect;
  GetClientRect(hwnd, &rect);

  size[0] = rect.right - rect.left;
  size[1] = rect.bottom - rect.top;

  return size;
}

// Gets the Win32 window handle
HWND cui_win32_window_getHandle() {
  return hwnd;
}
