// Name: fractals.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 10
// Description: Fractal Puzzles

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"

// Function prototypes
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
void draw_square(int xc, int yc, int radius);
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinking_squares(int xc, int yc, int radius);
void spiral_squares(int max_win, float angle, int spiral_radius, int sx, int sy, int square_radius);
void circular_lace(int xc, int yc, int radius);
void snowflake(int xc, int yc, int radius);
void tree(int xi, int yi, int length, float angle);
void fern(int xi, int yi, int length, float angle);
void spiral_spiral(double x, double y, double angle, double radius);


int main() {
  // Variables
  char c;
  int running = 1;

  int win_width = 700;
  int win_height = 700;
  int margin = 20;

  // Open the window
  gfx_open(win_width, win_height, "Fractal Puzzles");

  while (running) {
    // Get the user input
    c = gfx_wait();

    // Clear the screen
    gfx_clear();
    
    switch (c) {
    case 'q':
      // Quit the program
      running = 0;
      break;
    case '1':
      // Draw Sierpinski's Triangle
      sierpinski(margin, margin, win_width - margin, margin, win_width / 2, win_height - margin);
      break;
    case '2':
      // Draw Shrinking Squares
      shrinking_squares(win_width / 2, win_height / 2, win_height / 4 - (2*margin));
      break;
    case '3':
      // Draw Spiral Squares
      spiral_squares(win_height, 0, 0, win_width / 2, win_height / 2, 3);
      break;
    case '4':
      // Draw Circular Lace
      circular_lace(win_width / 2, win_height / 2, win_height / 3 - (2*margin));
      break;
    case '5':
      // Draw Snowflake
      snowflake(win_width / 2, win_height / 2, win_height / 4 - margin);
      break;
    case '6':
      // Draw Tree
      tree(win_width / 2, win_height - margin, win_height / 3, 0);
      break;
    case '7':
      // Draw Fern
      fern(win_width / 2, win_height - margin, win_height / 2, 0);
      break;
    case '8':
      // Draw Spiral of Spirals
      spiral_spiral(win_width / 2, win_height / 2, 0, win_height / 1.5);
      break;
    default:
      break;
    }
    
  }


  return 0;
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  // Draw three lines between three points making a triangle
  gfx_line(x1, y1, x2, y2);
  gfx_line(x2, y2, x3, y3);
  gfx_line(x3, y3, x1, y1);
}

void draw_square(int xc, int yc, int radius) {
  // Draw a square a given radius around a point
  int x1 = xc - radius;
  int x2 = xc + radius;
  int y1 = yc - radius;
  int y2 = yc + radius;
  
  gfx_line(x1, y1, x2, y1);
  gfx_line(x2, y1, x2, y2);
  gfx_line(x2, y2, x1, y2);
  gfx_line(x1, y2, x1, y1);
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

void shrinking_squares(int xc, int yc, int radius) {
  // Base case
  if (radius < 2) return;

  // Draw the square
  draw_square(xc, yc, radius);

  // Recursive calls
  shrinking_squares(xc - radius, yc - radius, radius / 2);
  shrinking_squares(xc + radius, yc - radius, radius / 2);
  shrinking_squares(xc - radius, yc + radius, radius / 2);
  shrinking_squares(xc + radius, yc + radius, radius / 2);
  
}

void spiral_squares(int max_win, float angle, int spiral_radius, int sx, int sy, int square_radius) {
  // Base case
  if (spiral_radius >= max_win || sx >= max_win || sy >= max_win) return;

  // Draw the square
  draw_square(sx, sy, square_radius);

  // Recursive call
  spiral_squares(max_win, angle + (M_PI / 6), spiral_radius + 10, sx + (spiral_radius * cos(angle)), sy + (spiral_radius * sin(angle)), square_radius + 3);

  
}

void circular_lace(int xc, int yc, int radius) {
  // Base case
  if (radius < 1) return;

  // Draw the circle
  gfx_circle(xc, yc, radius);

  // Recursive calls
  for (int i = 0; i < 6; i++) {
    circular_lace(xc + (radius * cos(M_PI / 3 * i)), yc + (radius * sin(M_PI / 3 * i)), radius / 3);
  }
}

void snowflake(int xc, int yc, int radius) {
  // Base case
  if (radius < 3) return;

  // Draw the snowflake
  for (int i = 0; i < 5; i++) {
    int xf = xc + radius * cos((((2*M_PI)/ 5) * i) + M_PI / 2);
    int yf = yc + radius * sin((((2*M_PI)/ 5) * i) + M_PI / 2);
    gfx_line(xc, yc, xf, yf);

    // Recursive calls
    snowflake(xf, yf, radius / 2.5);
  }
}

void tree(int xi, int yi, int length, float angle) {
  // Base case
  if (length < 1) return;

  // Draw the stem
  int xf = xi - length * sin(angle);
  int yf = yi - length * cos(angle);
  gfx_line(xi, yi, xf, yf);

  // Recursive calls
  tree(xf, yf, length / 1.5, angle + (M_PI / 6));
  tree(xf, yf, length / 1.5, angle - (M_PI / 6));
  
}

void fern(int xi, int yi, int length, float angle) {
  // Base case
  if (length < 2) return;

  // Draw the stem
  int xf = xi - length * sin(angle);
  int yf = yi - length * cos(angle);
  gfx_line(xi, yi, xf, yf);

  // Recursive calls
  for (int i = 0; i < 4; i++) {
    int xf_new = xf + ((length / 4) * sin(angle)) * i;
    int yf_new = yf + ((length / 4) * cos(angle)) * i;
    fern(xf_new, yf_new, length / 3, angle + (M_PI / 6));
    fern(xf_new, yf_new, length / 3, angle - (M_PI / 6));
  }
}

void spiral_spiral(double x, double y, double angle, double radius) {
  // Base case
  if (radius < 1) {
    gfx_point(x, y);
    return;
  }

  // Draw the smaller spiral
  double xp = x - radius * cos(angle);
  double yp = y + radius * sin(angle);
  spiral_spiral(xp, yp, angle, radius * 0.4);

  // Recursive call
  spiral_spiral(x, y, angle + M_PI / 5, radius * 0.9);
}


