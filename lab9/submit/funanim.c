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
void place_triangle(int tx, int ty, int lx, int ly, int rx, int ry);
void move_sun(Circle *sun_rotation, int clockwise);

int main() {
  char c;
  int clockwise = 1;


  // Open the window
  gfx_open(WIN_WIDTH, WIN_HEIGHT, "Rotating Animation");

  // Declare the wheel
  Circle wheel = {WIN_WIDTH / 2, WIN_HEIGHT / 2, 150, 0};


  // Declare and initialize the sun's rotational pattern
  Circle sun_rotation = {0, WIN_HEIGHT / 2, 30, M_PI};

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

    // Base of ferris wheel
    int top_ptx = wheel.px;
    int top_pty = wheel.py;
    int left_ptx = top_ptx - wheel.radius;
    int left_pty = top_pty + wheel.radius * 1.5;
    int right_ptx = top_ptx + wheel.radius;
    int right_pty = top_pty + wheel.radius * 1.5;
    gfx_color(0, 0, 0);
    place_triangle(top_ptx, top_pty, left_ptx, left_pty, right_ptx, right_pty);

    // Place/rotate the wheel
    rotate_circle(&wheel, clockwise);

    // Place the cars
    place_cars(wheel);

    // Place and move the sun
    move_sun(&sun_rotation, clockwise);

    // Text
    gfx_color(0, 0, 0);
    gfx_text(top_ptx - 80, left_pty + 20, "< and > to switch rotation");



    gfx_flush();

    
    usleep(50000);
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

    place_triangle(top_ptx, top_pty, left_ptx, left_pty, right_ptx, right_pty);
    
  }
}

void place_triangle(int tx, int ty, int lx, int ly, int rx, int ry) {

  // Place the triangle
  gfx_line(tx, ty, lx, ly);
  gfx_line(lx, ly, rx, ry);
  gfx_line(rx, ry, tx, ty);

}

void move_sun(Circle *sun_rotation, int clockwise) {
  if (clockwise) {
    // Move the position and angle of the sun
    sun_rotation->px = (WIN_WIDTH / 2) * cos(sun_rotation->angle) + (WIN_WIDTH / 2);
    sun_rotation->py = (WIN_HEIGHT / 2) * sin(sun_rotation->angle) + (WIN_HEIGHT / 2);
    sun_rotation->angle += (M_PI / 54);

    // If the sun goes past the horizon, set the position to the opposite side of the screen
    if (sun_rotation->angle >= M_PI * 2) {
      sun_rotation->px = 0;
      sun_rotation->py = WIN_HEIGHT / 2;
      sun_rotation->angle = M_PI;
    }
  } else {
    // Move the position and angle of the sun
    sun_rotation->px = (WIN_WIDTH / 2) * cos(sun_rotation->angle) + (WIN_WIDTH / 2);
    sun_rotation->py = (WIN_HEIGHT / 2) * sin(sun_rotation->angle) + (WIN_HEIGHT / 2);
    sun_rotation->angle -= (M_PI / 54);

    // If the sun goes past the horizon, set the position to the opposite side of the screen
    if (sun_rotation->angle <= M_PI) {
      sun_rotation->px = (WIN_WIDTH / 2) * cos(2 * M_PI) + (WIN_WIDTH / 2);
      sun_rotation->py = WIN_HEIGHT / 2;
      sun_rotation->angle = 2 * M_PI;
    }
  }

  // Display the circle
  gfx_color(204, 184, 53);
  gfx_circle(sun_rotation->px, sun_rotation->py, sun_rotation->radius);
}
