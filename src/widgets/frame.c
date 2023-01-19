#include <stdio.h>
#include <stdlib.h>

#define __cui_widgets_frame_includes__

#include <glad/glad.h>
#include "include/frame.h"

// Creates a new CUI frame component
CUIFrame *cui_widgets_frame_init(int x, int y, unsigned int width, unsigned int height, CUIColor *color) {
  CUIFrame *frame = malloc(sizeof(CUIFrame));

  // Set member variables
  frame->x = x;
  frame->y = y;
  frame->width = width;
  frame->height = height;

  frame->r = color->r;
  frame->g = color->g;
  frame->b = color->b;

  // Vertex & index data
  float vertices[] = {
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  // OpenGL buffers
  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  return frame;
}

// Destroys the frame
void cui_widgets_frame_destroy(CUIFrame *frame) {
  if (frame != NULL) {
    free(frame);
  }
}
