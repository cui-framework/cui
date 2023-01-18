#ifndef _window_h_
#define _window_h_

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
void cui_window_run(CUIWindow *window);

#endif
