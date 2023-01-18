#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define __cui_linux_window_includes__

#include "include/window.h"
#include "include/opengl.h"

#include <glad/glad.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

bool windowCreated = false;

Display *display;
Window window;
GC gc;
int screen;

Atom deleteWindow;

// Creates a new Linux X11 window
void cui_linux_window_new(unsigned int width, unsigned int height, const char *title) {
  if (!windowCreated) {
    windowCreated = true;

    display = XOpenDisplay((char*)0);
    screen = XDefaultScreen(display);

    // Foreground & background colors
    int white = XWhitePixel(display, screen);
    int black = XBlackPixel(display, screen);

    // X window attributes
    XSetWindowAttributes attribs;
    attribs.border_pixel = black;
    attribs.background_pixel = white;
    attribs.override_redirect = True;
    attribs.event_mask = ExposureMask;

    // Create the window
    window = XCreateWindow(display, RootWindow(display, screen), 300, 300, width, 
      height, 0, DefaultDepth(display, screen), InputOutput, VisualNoMask, 
      CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &attribs);

    if (!window) {
      printf("Error: Failed to create an X11 window.\n");
      exit(1);
    }

    // Redirect the closing
    deleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window, &deleteWindow, 1);

    XSetStandardProperties(display, window, title, title, None, NULL, 0, NULL);

    // Show the window
    XClearWindow(display, window);
    XMapRaised(display, window);

    // Create the context
    cui_linux_opengl_context();
    gladLoadGL();
    glViewport(0, 0, width, height);
  }
}

// Runs the X window
void cui_linux_window_run() {
  XEvent ev;

  while (true) {
    if (XPending(display) > 0) {
      XNextEvent(display, &ev);

      if (ev.type == ClientMessage) {
        if (ev.xclient.data.l[0] == deleteWindow) {
          break;
        }
      }

      if (ev.type == DestroyNotify) {
        break;
      }
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    cui_linux_opengl_render();
  }
}

// Closes the X window
void cui_linux_window_close() {
  XDestroyWindow(display, window);
}

// Gets the X11 display
Display *cui_linux_window_display() {
  return display;
}

// Gets the X11 window
Window cui_linux_window_window() {
  return window;
}
