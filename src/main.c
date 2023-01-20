#include <stdio.h>
#include <stdlib.h>

#include <cglm/cglm.h>
#include "include/color.h"

#include "widgets/include/frame.h"
#include "widgets/include/image.h"
#include "widgets/include/window.h"

int main(int argc, char *argv[]) {
  CUIWindowAttribs attribs;
  attribs.width = 1280;
  attribs.height = 720;
  attribs.title = "Hello CUI!";

  CUIWindow wnd = cui_window_init(attribs);

  CUIImage *img = cui_widgets_image_init(10, 10, 200, 200, "../res/gfx/test.png");
  CUIFrame *frame = cui_widgets_frame_init(220, 10, 200, 200, cui_color_create(200, 0, 0));

  cui_window_addImage(img);
  cui_window_run(&wnd);

  return 0;
}
