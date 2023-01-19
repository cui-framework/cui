#include <stdio.h>
#include <stdlib.h>

#include "include/utils.h"
#include "include/renderer.h"

#include <glad/glad.h>

unsigned int frameVao;
unsigned int frameProgram;

// Initializes the frame renderer
void cui_renderer_initFrame() {
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

  // VAO
  glGenVertexArrays(1, &frameVao);
  glBindVertexArray(frameVao);

  // Destroy unneeded things
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  free((void*)vertexShaderSource);
  free((void*)fragmentShaderSource);
}

// Does any other tasks needed to be done before the main loop
void cui_renderer_finalize() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

// Does any tasks before drawing
void cui_renderer_preDraw() {
  glUseProgram(frameProgram);
  glBindVertexArray(frameVao);
}

// Gets the frame renderer's shader program handle
unsigned int cui_renderer_getFrameProgram() {
  return frameProgram;
}
