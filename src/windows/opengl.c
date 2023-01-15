#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <glad/glad.h>
#include <gl/wglext.h>

#define __cui_windows_window_include__

#include "include/opengl.h"
#include "include/window.h"

// OpenGL procedure types
typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, 
  HGLRC hShareContext, const int *attribList);

typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int *piAttribIList,
  const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

// OpenGL procedures
wglCreateContextAttribsARB_type *wglCreateContextAttribsARB;
wglChoosePixelFormatARB_type *wglChoosePixelFormatARB;

HDC hdc;

// Initializes OpenGL context creation
void cui_win32_opengl_init() {
  // Create a temporary OpenGL context..

  // Temporary window class
  WNDCLASSW wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = DefWindowProcW;
  wc.hInstance = GetModuleHandleW(NULL);
  wc.lpszClassName = L"-cui-gl-"; // TODO: salt this as well

  if (!RegisterClassW(&wc)) {
    printf("Error: Faild to register a temporary GL window class.\n");
    exit(1);
  }

  // Temporary window
  HWND tmp = CreateWindowExW(
    0,
    wc.lpszClassName,
    L"Temporary OpenGL Window",
    0,
    0,
    0,
    200,
    200,
    NULL,
    NULL,
    wc.hInstance,
    NULL
  );

  HDC tmpHdc = GetDC(tmp);

  // Set the temporary window's pixel format
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.cColorBits = 32;
  pfd.cAlphaBits = 8;
  pfd.iLayerType = PFD_MAIN_PLANE;
  pfd.cDepthBits = 24;
  pfd.cStencilBits = 8;

  // FIXME: no error handling

  int pf = ChoosePixelFormat(tmpHdc, &pfd);
  SetPixelFormat(tmpHdc, pf, &pfd);

  // Create the temporary context
  HGLRC tmpContext = wglCreateContext(tmpHdc);
  wglMakeCurrent(tmpHdc, tmpContext);

  // Load the functions needed
  wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)
    wglGetProcAddress("wglCreateContextAttribsARB");
  
  wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)
    wglGetProcAddress("wglChoosePixelFormatARB");
  
  // Free unneeded stuff
  wglMakeCurrent(tmpHdc, 0);
  wglDeleteContext(tmpContext);
  ReleaseDC(tmp, tmpHdc);
  DestroyWindow(tmp);
}

// Creates an actual OpenGL context
void cui_win32_opengl_context() {
  hdc = GetDC(cui_win32_window_getHandle());

  // Choose a pixel format the modern way
  int pfa[] = {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    0
  };

  int pf;
  UINT numFormats;
  wglChoosePixelFormatARB(hdc, pfa, 0, 1, &pf, &numFormats);

  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, pf, sizeof(pfd), &pfd);
  SetPixelFormat(hdc, pf, &pfd);

  // Create the modern OpenGL 3.3 context
  int glAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };

  HGLRC context = wglCreateContextAttribsARB(hdc, 0, glAttribs);
  wglMakeCurrent(hdc, context);
  gladLoadGL();
}

// Renders everything to the screen
void cui_win32_opengl_present() {
  SwapBuffers(hdc);
}
