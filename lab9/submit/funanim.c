// Name: funanim.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 9 Part 3
// Description: Rotating Animation
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "gfx.h"

// Global Variables
#define WIN_WIDTH 1000
#define WIN_HEIGHT 800
#define CART_SIZE 20

// Structs
typedef struct {
  int px;
  int py;
  int radius;
  float angle;
} Circle;

// Function Prototypes
void rotate_circle(Circle *circle, int clockwise);
void place_cars(Circle circle);
void solid_triangle(int tx, int ty, int lx, int ly, int rx, int ry);

int main() {
  char c;
  int clockwise = 1;


  // Open the window
  gfx_open(WIN_WIDTH, WIN_HEIGHT, "Rotating Animation");

  // Declare the circle
  Circle wheel = {WIN_WIDTH / 2, WIN_HEIGHT / 2, 150, 0};

  // Set the background to white
  gfx_clear_color(166, 215, 227);


  while (1) {

    if (gfx_event_waiting()) {
      // Get the interaction
      c = gfx_wait();
      if (c == 'q') break;
      else if (c == 83) clockwise = 1;
      else if (c == 81) clockwise = 0;
    }

    gfx_clear();

    // Base
    int top_ptx = wheel.px;
    int top_pty = wheel.py;
    int left_ptx = top_ptx - wheel.radius;
    int left_pty = top_pty + wheel.radius * 1.5;
    int right_ptx = top_ptx + wheel.radius;
    int right_pty = top_pty + wheel.radius * 1.5;
    gfx_line(top_ptx, top_pty, left_ptx, left_pty);
    gfx_line(left_ptx, left_pty, right_ptx, right_pty);
    gfx_line(right_ptx, right_pty, top_ptx, top_pty);
    
    rotate_circle(&wheel, clockwise);
    place_cars(wheel);



    gfx_flush();

    
    usleep(100000);
  }

  return 0;
}

void rotate_circle(Circle *circle, int clockwise) {
  // Color to blue
  gfx_color(0, 0, 255);

  // Increase angle
  if (clockwise) {
    circle->angle += (M_PI / 54);
  } else {
    circle->angle -= (M_PI / 54);
  }
  
  // Draw circle
  gfx_circle(circle->px, circle->py, circle->radius);
  
  // Draw 6 lines
  for (int i = 1; i <= 6; i++) {
    gfx_line(circle->px, circle->py, circle->px + (circle->radius * cos(M_PI / 3 * i + circle->angle)), circle->py + (circle->radius * sin(M_PI / 3 * i + circle->angle)));
  }


}

void place_cars(Circle circle) {
  // Color to pink
  gfx_color(214, 21, 115);

  
  for (int i = 1; i <= 6; i++) {
    int top_ptx = circle.px + (circle.radius * cos(M_PI / 3 * i + circle.angle));
    int top_pty = circle.py + (circle.radius * sin(M_PI / 3 * i + circle.angle));
    int left_ptx = top_ptx - CART_SIZE;
    int left_pty = top_pty + CART_SIZE;
    int right_ptx = top_ptx + CART_SIZE;
    int right_pty = top_pty + CART_SIZE;

    
    gfx_line(top_ptx, top_pty, left_ptx, left_pty);
    gfx_line(left_ptx, left_pty, right_ptx, right_pty);
    gfx_line(right_ptx, right_pty, top_ptx, top_pty);
    

    //solid_triangle(top_ptx, top_pty, left_ptx, left_pty, right_ptx, right_pty);
  }
}

void solid_triangle(int tx, int ty, int lx, int ly, int rx, int ry) {
  // Color to pink
  gfx_color(214, 21, 115);
  int top_ptx = tx;
  int top_pty = ty;
  int left_ptx = lx;
  int left_pty = ly;
  int right_ptx = rx;
  int right_pty = ry;
  
  for (int i = 0; i <= abs(tx - lx); i++) {
    gfx_line(top_ptx, top_pty, left_ptx, left_pty);
    gfx_line(left_ptx, left_pty, right_ptx, right_pty);
    gfx_line(right_ptx, right_pty, top_ptx, top_pty);

    top_pty++;
    left_ptx++; left_pty--;
    right_ptx--; right_pty--;
  }

}
