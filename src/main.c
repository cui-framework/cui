#include <stdio.h>
#include <stdlib.h>

#include "macos/include/window.h"

int main(int argc, char *argv[]) {
  cui_macos_window_new(1280, 720, "CUI Linux Test");
  cui_macos_window_run();
  cui_macos_window_close();

  return 0;
}
