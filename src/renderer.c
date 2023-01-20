#include <stdio.h>
#include <stdlib.h>

#include "include/utils.h"
#include "include/renderer.h"

#include <glad/glad.h>

unsigned int frameVao;
unsigned int frameProgram;

unsigned int imageVao;
unsigned int imageProgram;

// Initializes the frame renderer
void cui_renderer_initFrame() {
  // VAO
  glGenVertexArrays(1, &frameVao);
  glBindVertexArray(frameVao);

  // Shader sources
  const char *vertexShaderSource = utils_readFile("../src/shaders/frame/shader.vert");
  const char *fragmentShaderSource = utils_readFile("../src/shaders/frame/shader.frag");

  // Shaders
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Shader program
  frameProgram = glCreateProgram();
  glAttachShader(frameProgram, vertexShader);
  glAttachShader(frameProgram, fragmentShader);
  glLinkProgram(frameProgram);

  // Destroy unneeded things
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  free((void*)vertexShaderSource);
  free((void*)fragmentShaderSource);
}

// Does any other tasks needed to be done before the main loop for the frame renderer
void cui_renderer_finalizeFrame() {
  glBindVertexArray(frameVao);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

// Does any tasks before drawing
void cui_renderer_preDrawFrame() {
  glUseProgram(frameProgram);
  glBindVertexArray(frameVao);
}

// Initializes image rendering
void cui_renderer_initImage() {
  // VAO
  glGenVertexArrays(1, &imageVao);
  glBindVertexArray(imageVao);

  // Shader sources
  const char *vertexShaderSource = utils_readFile("../src/shaders/image/shader.vert");
  const char *fragmentShaderSource = utils_readFile("../src/shaders/image/shader.frag");

  // Shaders
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Shader program
  imageProgram = glCreateProgram();
  glAttachShader(imageProgram, vertexShader);
  glAttachShader(imageProgram, fragmentShader);
  glLinkProgram(imageProgram);

  // Destroy unneeded things
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  free((void*)vertexShaderSource);
  free((void*)fragmentShaderSource);
}

// Does any other tasks needed to be done before the main loop for the image renderer
void cui_renderer_finalizeImage() {
  glBindVertexArray(imageVao);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

// Does any tasks before drawing for the image renderer
void cui_renderer_preDrawImage() {
  glUseProgram(imageProgram);
  glBindVertexArray(imageVao);
}

// Gets the frame renderer's shader program handle
unsigned int cui_renderer_getFrameProgram() {
  return frameProgram;
}

// Gets the frame renderer's shader program handle
unsigned int cui_renderer_getImageProgram() {
  return imageProgram;
}

// Gets the frame renderer's VAO handle
unsigned int cui_renderer_getFrameVao() {
  return frameVao;
}

// Gets the frame renderer's VAO handle
unsigned int cui_renderer_getImageVao() {
  return imageVao;
}
