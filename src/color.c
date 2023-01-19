#include <stdio.h>
#include <stdlib.h>

#include "include/color.h"

// Creates a new color
CUIColor *cui_color_create(int red, int green, int blue) {
  CUIColor *color = malloc(sizeof(CUIColor));

  color->r = red;
  color->g = green;
  color->b = blue;

  return color;
}

// Destroys the color
void cui_color_destroy(CUIColor *color) {
  if (color != NULL) {
    free(color);
  }
}
