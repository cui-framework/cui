#include <stdio.h>
#include <stdlib.h>

#include "widgets/include/window.h"

int main(int argc, char *argv[]) {
  CUIWindowAttribs attribs;
  attribs.width = 1280;
  attribs.height = 720;
  attribs.title = "Hello CUI!";

  CUIWindow wnd = cui_window_init(attribs);
  cui_window_run(&wnd);

  return 0;
}
