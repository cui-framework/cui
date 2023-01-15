#ifndef _window_h_
#define _window_h_

void cui_win32_window_new(unsigned int width, unsigned int height, const char *title);
void cui_win32_window_run();
void cui_win32_window_close();

#ifdef __cui_windows_window_include__
#include <Windows.h>
HWND cui_win32_window_getHandle(); 
#endif

#endif
