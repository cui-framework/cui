#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define __cui_linux_window_includes__

#include "include/window.h"
#include "include/opengl.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <glad/glad.h>
#include <GL/glx.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

Display *disp;
Window drawable;

// Creates an X11 OpenGL context
void cui_linux_opengl_context() {
  disp = cui_linux_window_display();
  drawable = cui_linux_window_window();
  int screen = XDefaultScreen(disp);

  int glxAttribs[] = {
    GLX_X_RENDERABLE, True,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
    GLX_DEPTH_SIZE, 24,
    GLX_STENCIL_SIZE, 8,
    GLX_DOUBLEBUFFER, True,
    0
  };

  int fbCount;
  GLXFBConfig *fbConfig = glXChooseFBConfig(disp, screen, glxAttribs, &fbCount);

  if (fbConfig == 0) {
    printf("Error: Failed to retrieve framebuffer configuration.\n");
    exit(1);
  }

  // Load the function
  glXCreateContextAttribsARBProc glXCreateContextAttribsARB;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
    glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
  
  // Configure the OpenGL context
  int glAttribs[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 3,
    GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
    None
  };

  // Create the context
  GLXContext context = glXCreateContextAttribsARB(disp, *fbConfig, 0, 1, glAttribs);
  glXMakeCurrent(disp, drawable, context);
}

// Swaps both buffers to render
void cui_linux_opengl_render() {
  glXSwapBuffers(disp, drawable);
}
