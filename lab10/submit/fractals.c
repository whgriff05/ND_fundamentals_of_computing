// Name: fractals.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 10
// Description: Fractal Puzzles

#include <stdlib.h>


#include "gfx.h"

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);

int main() {
  char c;
  int running = 1;

  int win_width = 700;
  int win_height = 700;
  int margin = 20;

  // Open the window
  gfx_open(win_width, win_height, "Fractal Puzzles");

  while (running) {    
    c = gfx_wait();

    gfx_clear();
    
    switch (c) {
    case 'q':
      running = 0;
      break;
    case '1':
      sierpinski(margin, margin, win_width - margin, margin, win_width / 2, win_height - margin);
    default:
      break;
    }
    
  }


  return 0;
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  gfx_line(x1, y1, x2, y2);
  gfx_line(x2, y2, x3, y3);
  gfx_line(x3, y3, x1, y1);
}

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3) {
  // Base case. 
  if( abs(x2-x1) < 5 ) return;

  // Draw the triangle
  draw_triangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

