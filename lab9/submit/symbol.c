#include "gfx.h"


int main() {
  char c;

  gfx_open(1000, 800, "My First Window");

  while (1) {

    c = gfx_wait();
    if (c == 'q') break;
  }

  return 0;
}
