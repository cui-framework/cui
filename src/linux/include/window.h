#ifndef _linux_window_h_
#define _linux_window_h_

void cui_linux_window_new(unsigned int width, unsigned int height, const char *title);
void cui_linux_window_update();
int cui_linux_window_active();
void cui_linux_window_close();

#ifdef __cui_linux_window_includes__
  #include <X11/Xlib.h>

  Display *cui_linux_window_display();
  Window cui_linux_window_window();
#endif

#endif
