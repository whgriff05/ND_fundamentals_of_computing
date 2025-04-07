// test_colors.c
// the line and circle colors change for certain key presses

#include "gfx.h"

int main()
{
  int wd = 500;  // window width
  int ht = 400;  // window height
  char c;

  gfx_open(wd, ht, "My window");  // Open a new window for drawing.

  gfx_color(0,0,255);      // Set the initial drawing color (blue)

  while(1) {
    gfx_clear();                // clear the window 
    gfx_line(100,300,250,150);  // draw a line
    gfx_circle(300,200,50);     // draw a circle
    gfx_flush();                // flush all output to the window

    c = gfx_wait();             // wait for user input (event)
    if (c == 'q') break;        // quit if 'q' is pressed
    switch(c) {
      case 'r':
        gfx_color(255,0,0);     // change to red if 'r' is pressed
        break;
      case 'g':
        gfx_color(0,255,0);     // change to green if 'g' is pressed
        break;
      case 'b':
        gfx_color(0,0,255);     // change to blue if 'b' is pressed
        break;
      case 'y':
        gfx_color(255,255,0);   // change to yellow if 'y' is pressed
        break;
      case 'c':
        gfx_color(0,255,255);   // change to cyan if 'c' is pressed
        break;
      case 'm':
        gfx_color(255,0,255);   // change to magenta if 'm' is pressed
        break;
      case 'w':
        gfx_color(255,255,255); // change to white if 'w' is pressed
        break;
      default:                  // do nothing for any other key
        break;
    }
  }

  return 0;
}

