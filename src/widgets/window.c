#include <stdio.h>
#include <stdlib.h>

#define __cui_widgets_window_includes__
#define __cui_widgets_frame_includes__

#include <glad/glad.h>
#include <cglm/cglm.h>

#include "include/window.h"
#include "../include/renderer.h"

void cui_window_update();

#ifdef __APPLE__
  #include "../macos/include/window.h"
#elif _WIN32
  #include "../windows/include/window.h"
#elif __linux__
  #include "../linux/include/window.h"
#endif

CUIFrame **frames;
mat4 projection;
int framesCount = 0;

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

  cui_renderer_initFrame();
  glm_ortho(0.0f, (float)attribs.width, (float)attribs.height, 0.0f, -1.0f, 1.0f, projection);

  return wnd;
}

// Runs the native, cross platform window
void cui_window_run(CUIWindow *window) {
  cui_renderer_finalize();

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

// Adds a frame to the window's renderer
void cui_window_addFrame(CUIFrame *frame) {
  if (framesCount == 0) {
    frames = malloc(sizeof(CUIFrame));
  } else {
    frames = realloc(frames, (framesCount + 1) * sizeof(CUIFrame));
  }

  frames[framesCount] = frame;
  framesCount++;
}

// Updates the window (only called by CUI itself)
void cui_window_update() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  cui_renderer_preDraw();

  // Apply the projection matrix
  int projectionLoc = glGetUniformLocation(cui_renderer_getFrameProgram(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection[0]);

  // Object rendering
  for (int i = 0; i < framesCount; i++) {
    // Compute model matrix
    glm_mat4_identity(frames[i]->model);

    vec3 transformation = {frames[i]->x + (frames[i]->width / 2), frames[i]->y + (frames[i]->height / 2), 0.0f};
    vec3 scale = {frames[i]->width, frames[i]->height, 0.0f};

    glm_translate(frames[i]->model, transformation);
    glm_scale(frames[i]->model, scale);

    // Apply the model matrix
    int modelLoc = glGetUniformLocation(cui_renderer_getFrameProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, frames[i]->model[0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
