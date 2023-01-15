#include <stdio.h>
#include <stdlib.h>

#include "windows/include/window.h"

int main(int argc, char *argv[]) {
  cui_win32_window_new(1280, 720, "CUI Test");
  cui_win32_window_run();
  cui_win32_window_close();  

  return 0;
}
