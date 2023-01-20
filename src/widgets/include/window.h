#ifndef _window_h_
#define _window_h_

#ifdef __cui_widgets_window_includes__
  #include "frame.h"
  #include "image.h"
#endif

typedef struct
{
  int closed;
} CUIWindow;

typedef struct
{
  unsigned int width;
  unsigned int height;
  char *title;
} CUIWindowAttribs;

CUIWindow cui_window_init(CUIWindowAttribs attribs);
void cui_window_addFrame(CUIFrame *frame);
void cui_window_addImage(CUIImage *image);
void cui_window_run(CUIWindow *window);

#endif
