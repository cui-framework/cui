#ifndef _image_h_
#define _image_h_

#ifdef __cui_widgets_image_includes__
  #include <cglm/cglm.h>
#endif

typedef struct
{
  int x, y;
  unsigned int width, height;
  unsigned int texture;
  mat4 model;
} CUIImage;

CUIImage *cui_widgets_image_init(int x, int y, unsigned int width, unsigned int height, const char *filepath);
void cui_widgets_image_destroy(CUIImage *img);

#endif
