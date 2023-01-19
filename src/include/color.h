#ifndef _color_h_
#define _color_h_

typedef struct
{
  int r, g, b;
} CUIColor;

CUIColor *cui_color_create(int r, int g, int b);
void cui_color_destroy(CUIColor *color);

#endif
