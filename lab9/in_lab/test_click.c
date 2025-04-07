// test_click.c
//  example to test how to get the position of the mouse click
//  a small circle will be drawn wherever the mouse is clicked
//  hitting the ESC key (ascii value of 27) will clear the window
//  hitting the 'q' key will end the program
//
#include <stdio.h>
#include "gfx.h"

int main()
{
  int wd = 500, ht = 400;  // window width, height
  int xm, ym;              // mouse's position (when an event occurs)
  char c;    // the key that's pressed, or the mouse button that's clicked

  gfx_open(wd, ht, "My window"); // Open a new window for drawing 

  while(1) {
    c = gfx_wait();        // wait for a user event
    xm = gfx_xpos();       // get mouse's x coordinate
    ym = gfx_ypos();       // get mouse's y coordinate

    if (c == 1) {       // left mouse button was clicked
      gfx_circle(xm, ym, 5);       // draw a tiny circle at that location
      printf("(%d,%d)\n", xm, ym); // display the click's coord. at the terminal
    }

    if (c == 27) gfx_clear();   // the ESC key was pressed  
    if (c == 'q') break;        // the 'q' key was pressed
  }

  return 0;
}

