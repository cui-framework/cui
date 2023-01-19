#include <stdio.h>
#include <stdlib.h>

#include "include/color.h"

#include "widgets/include/frame.h"
#include "widgets/include/window.h"

int main(int argc, char *argv[]) {
  CUIWindowAttribs attribs;
  attribs.width = 1280;
  attribs.height = 720;
  attribs.title = "Hello CUI!";

  CUIWindow wnd = cui_window_init(attribs);

  CUIFrame *frame = cui_widgets_frame_init(10, 10, 200, 200, cui_color_create(255, 0, 255));

  cui_window_addFrame(frame);
  cui_window_run(&wnd);

  return 0;
}
