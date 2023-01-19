#include <stdio.h>
#include <stdlib.h>

#include "include/utils.h"

// Reads a file
char *utils_readFile(const char *filepath) {
  // Open the file
  FILE *file = fopen(filepath, "rb");
  
  if (!file) {
    printf("Error: Failed to read file \"%s\". Does it exist?\n", filepath);
    exit(1);
  }

  // Get the length of the file
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Read the file
  char *content = malloc(length + 1);
  fread(content, length, 1, file);
  content[length] = '\0';

  // Return
  fclose(file);
  return content;
}
