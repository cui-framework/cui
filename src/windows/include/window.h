#ifndef _windows_window_h_
#define _windows_window_h_

void cui_win32_window_new(unsigned int width, unsigned int height, const char *title);
void cui_win32_window_update();
int cui_win32_window_active();
void cui_win32_window_close();

int *cui_win32_window_getSize();

#ifdef __cui_windows_window_include__
#include <Windows.h>
HWND cui_win32_window_getHandle(); 
#endif

#endif
