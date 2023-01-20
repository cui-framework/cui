#include <stdio.h>
#include <stdlib.h>

#define __cui_widgets_image_includes__
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
int framesCount = 0;

CUIImage **images;
int imagesCount = 0;

mat4 projection;

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

    int *size = cui_win32_window_getSize();
    glViewport(0, 0, size[0], size[1]);
  #endif

  cui_renderer_initFrame();
  cui_renderer_initImage();

  glm_ortho(0.0f, (float)attribs.width, (float)attribs.height, 0.0f, -1.0f, 1.0f, projection);

  return wnd;
}

// Runs the native, cross platform window
void cui_window_run(CUIWindow *window) {
  cui_renderer_finalizeFrame();
  cui_renderer_finalizeImage();

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

// Adds an image to the window's renderer
void cui_window_addImage(CUIImage *image) {
  if (imagesCount = 0) {
    images = malloc(sizeof(CUIImage));
  } else {
    images = realloc(images, (imagesCount + 1) * sizeof(CUIImage));
  }

  images[imagesCount] = image;
  imagesCount++;
}

// Updates the window (only called by CUI itself)
void cui_window_update() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  /// Frame rendering
  cui_renderer_preDrawFrame();
  glBindVertexArray(cui_renderer_getFrameVao());

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

    // Compute & apply the color
    vec3 color = {frames[i]->r, frames[i]->g, frames[i]->b};
    int colorLoc = glGetUniformLocation(cui_renderer_getFrameProgram(), "color");
    glUniform3fv(colorLoc, 1, color);

    // Apply the model matrix
    int modelLoc = glGetUniformLocation(cui_renderer_getFrameProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, frames[i]->model[0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
  
  glBindVertexArray(0);

  /// Image rendering
  cui_renderer_preDrawImage();
  glBindVertexArray(cui_renderer_getImageVao());

  // Apply the projection matrix
  int projectionLocImg = glGetUniformLocation(cui_renderer_getImageProgram(), "projection");
  glUniformMatrix4fv(projectionLocImg, 1, GL_FALSE, projection[0]);

  // Object rendering
  for (int i = 0; i < imagesCount; i++) {
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, images[i]->texture);

    // Compute model matrix
    glm_mat4_identity(images[i]->model);

    vec3 transformation = {images[i]->x + (images[i]->width / 2), images[i]->y + (images[i]->height / 2), 0.0f};
    vec3 scale = {images[i]->width, images[i]->height, 0.0f};

    glm_translate(images[i]->model, transformation);
    glm_scale(images[i]->model, scale);

    // Apply the model matrix
    int modelLoc = glGetUniformLocation(cui_renderer_getImageProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, images[i]->model[0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  glBindVertexArray(0);
}
