#ifndef _widgets_frame_h_
#define _widgets_frame_h_

#ifdef __cui_widgets_frame_includes__
  #include "../../include/color.h"
#endif

#include <cglm/cglm.h>

typedef struct
{
  mat4 model;
  int x, y;
  int r, g, b;
  unsigned int width, height;
} CUIFrame;

CUIFrame *cui_widgets_frame_init(int x, int y, unsigned int width, unsigned int height, CUIColor *color);
void cui_widgets_frame_destroy(CUIFrame *frame);

#endif
