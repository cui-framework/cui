#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#define __cui_widgets_image_includes__

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "../include/renderer.h"
#include "include/image.h"

// Creates a new image widget
CUIImage *cui_widgets_image_init(int x, int y, unsigned int width, unsigned int height, const char *filepath) {
  glBindVertexArray(cui_renderer_getImageVao());
  CUIImage *img = malloc(sizeof(CUIImage));

  // Set member variables
  img->x = x;
  img->y = y;
  img->width = width;
  img->height = height;

  // Vertex & index data
  float vertices[] = {
    0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,       1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  // Buffers
  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Create the texture
  glGenTextures(1, &img->texture);
  glBindTexture(GL_TEXTURE_2D, img->texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // Load the image
  int w, h, nrChannels;
  unsigned char *data = stbi_load(filepath, &w, &h, &nrChannels, 0);

  if (data == NULL) {
    printf("Error: Failed to load an image with filepath \"%s\". Does it exist?\n", filepath);
    exit(1);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glBindVertexArray(0);

  return img;
}

// Destroys the image
void cui_widgets_image_destroy(CUIImage *img) {
  if (img != NULL) {
    free(img);
  }
}
