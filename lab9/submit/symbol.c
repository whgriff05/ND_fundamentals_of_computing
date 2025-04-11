// Name: symbol.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 9 Part 1
// Description: Symbolic Typewriter
#include <math.h>
#include "gfx.h"

// Global Variables
#define SIZE 50

// Function Prototypes
void display_square(int size, int xpos, int ypos);
void display_circle(int size, int xpos, int ypos);
void display_triangle(int size, int xpos, int ypos);
void display_polygon(int size, int xpos, int ypos, int sides);


int main() {
  char c;

  // Open the window
  gfx_open(1000, 800, "Symbolic Typewriter");

  while (1) {

    // Get the input character
    c = gfx_wait();
    // Get the mouse position
    int xpos = gfx_xpos();
    int ypos = gfx_ypos(); 

    // If the q key is pressed, end the program
    if (c == 'q') break;

    switch (c) {
    case 1:
      // If mouse1 is pressed, display a square
      display_square(SIZE, xpos, ypos);
      break;
    case 'c':
      // If c is pressed, display a circle
      display_circle(SIZE, xpos, ypos);
      break;
    case 't':
      // If t is pressed, display a triangle
      display_triangle(SIZE, xpos, ypos);
      break;
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      // If a number key 3-9 is pressed, display a polygon with n sides (n = number key)
      display_polygon(SIZE, xpos, ypos, (int)c - 48);
      break;
    case 27:
      // If the escape key is pressed, clear the screen
      gfx_clear();
    default:
      break;
    }

    // Flush the output to the screen
    gfx_flush();
  }

  return 0;
}

void display_square(int size, int xpos, int ypos) {
  int minx, maxx, miny, maxy;
  // Calculate the minimum and maximum x and y positions for the square
  minx = xpos - (size / 2);
  maxx = xpos + (size / 2);
  miny = ypos - (size / 2);
  maxy = ypos + (size / 2);

  // Set the color to blue
  gfx_color(0, 0, 255);

  // Display four lines to make a square
  gfx_line(minx, miny, maxx, miny);
  gfx_line(maxx, miny, maxx, maxy);
  gfx_line(maxx, maxy, minx, maxy);
  gfx_line(minx, maxy, minx, miny);
}

void display_circle(int size, int xpos, int ypos) {
  // Set the color to white
  gfx_color(255, 255, 255);

  // Display a circle centered at the mouse
  gfx_circle(xpos, ypos, size / 2);
}

void display_triangle(int size, int xpos, int ypos) {
  int pointx, pointy;
  int rx, ry, lx, ly;
  
  // Calculate each endpoint's x and y coords
  pointx = xpos;
  pointy = ypos - (size / 2);
  rx = xpos - (size / 2);
  ry = ypos + (size / 2);
  lx = xpos + (size / 2);
  ly = ypos + (size / 2);

  // Set the color to green
  gfx_color(0, 255, 0);

  // Display the three lines between the points to make the triangle
  gfx_line(rx, ry, pointx, pointy);
  gfx_line(pointx, pointy, lx, ly);
  gfx_line(lx, ly, rx, ry);
}

void display_polygon(int size, int xpos, int ypos, int sides) {
  // Calculate the angle division each line will be placed between
  float divs = (2 * M_PI) / sides;

  // Set the color to purple
  gfx_color(255, 0, 255);

  // For the amount of sides in the shape
  // Draw a line between two points around the mouse position
  // Using polar coordinates where x = r * cos(theta) and y = r * sin(theta)
  // Points are calculated by starting at the position of the mouse, then adding the offset of half the size times sin/cos the angle of the point
  for (int i = 1; i <= sides; i++) {
    gfx_line(xpos + (size / 2) * cos(divs * (i - 1)), ypos + (size / 2) * sin(divs * (i - 1)), xpos + (size / 2) * cos(divs * i), ypos + (size / 2) * sin(divs * i));
  }

  
}
