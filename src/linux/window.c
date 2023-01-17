#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

bool windowCreated = false;

Display *display;
Window window;
GC gc;
int screen;

// Creates a new Linux X11 window
void cui_linux_window_new(unsigned int width, unsigned int height, const char *title) {
  if (!windowCreated) {
    windowCreated = true;

    display = XOpenDisplay((char*)0);
    screen = XDefaultScreen(display);

    // Foreground & background colors
    int white = XWhitePixel(display, screen);
    int black = XBlackPixel(display, screen);

    // Create the window
    window = XCreateSimpleWindow(display, XDefaultRootWindow(display), 
      300, 300, width, height, 5, black, white);

    if (!window) {
      printf("Error: Failed to create an X11 window.\n");
      exit(1);
    }

    XSetStandardProperties(display, window, title, title, None, NULL, 0, NULL);
    gc = XCreateGC(display, window, 0, 0);

    XSetBackground(display, gc, white);
    XSetForeground(display, gc, black);

    // Show the window
    XClearWindow(display, window);
    XMapRaised(display, window);
  }
}

// Runs the X window
void cui_linux_window_run() {
  XEvent ev;

  while (true) {
    XNextEvent(display, &ev);
  }
}

// Closes the X window
void cui_linux_window_close() {
  XDestroyWindow(display, window);
}
