#ifndef _mac_window_h_
#define _mac_window_h_

void cui_macos_window_new(unsigned int width, unsigned int height, const char *title);
void cui_macos_window_update();
int cui_macos_window_active();
void cui_macos_window_close();

#endif
