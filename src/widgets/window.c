#include <stdio.h>
#include <stdlib.h>

#include "include/window.h"

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
    cui_macos_window_run();
  #elif __linux__
    cui_linux_window_run();
  #elif _WIN32
    cui_win32_window_run();
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
