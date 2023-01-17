#include <stdio.h>
#include <stdlib.h>

#include "linux/include/window.h"

int main(int argc, char *argv[]) {
  cui_linux_window_new(1280, 720, "CUI Linux Test");
  cui_linux_window_run();
  cui_linux_window_close();

  return 0;
}
