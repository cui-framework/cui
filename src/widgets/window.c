#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include "include/window.h"

void cui_window_update();

#ifdef __APPLE__
  #include "../macos/include/window.h"
#elif _WIN32
  #include "../windows/include/window.h"
#elif __linux__
  #include "../linux/include/window.h"
#endif

// Creates a new CUI window instance.
CUIWindow cui_window_init(CUIWindowAttribs attribs) {
  CUIWindow wnd;
  wnd.closed = 0;

  // Create the window
  #ifdef __APPLE__
    cui_macos_window_new(attribs.width, attribs.height, attribs.title);
  #elif __linux__
    cui_linux_window_new(attribs.width, attribs.height, attribs.title);
  #elif _WIN32
    cui_win32_window_new(attribs.width, attribs.height, attribs.title);
  #endif

  return wnd;
}

// Runs the native, cross platform window
void cui_window_run(CUIWindow *window) {
  #ifdef __APPLE__
    while (cui_macos_window_active()) {
      cui_window_update();
      cui_macos_window_update();
    }
  #elif __linux__
    while (cui_linux_window_active()) {
      cui_window_update();
      cui_linux_window_update();
    }
  #elif _WIN32
    while (cui_win32_window_active()) {
      cui_window_update();
      cui_win32_window_update();
    }
  #endif

  window->closed = 1;

  #ifdef __APPLE__
    cui_macos_window_close();
  #elif __linux__
    cui_linux_window_close();
  #elif _WIN32
    cui_win32_window_close();
  #endif
}

// Updates the window (only called by CUI itself)
void cui_window_update() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
