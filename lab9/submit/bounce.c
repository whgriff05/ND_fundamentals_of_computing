// Name: bounce.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 9 Part 2
// Description: Bouncing Ball
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "gfx.h"

// Global Variables
#define WIN_WIDTH 1000
#define WIN_HEIGHT 800
#define BALL_RADIUS 25

// Function Prototypes
void gen_velocity(int *vx, int *vy);
void move_ball(int *px, int *py, int *vx, int *vy);
void test_bounds(int *px, int *py, int *vx, int *vy);

int main() {
  char c;
  int running = 1;

  // Seed the random number generator
  srand(time(NULL));

  // Ball position and velocity variables
  int ballx = WIN_WIDTH / 2, bally = WIN_HEIGHT / 2;
  int vx, vy;

  // Generate starting velocities
  gen_velocity(&vx, &vy);

  // Open the window
  gfx_open(WIN_WIDTH, WIN_HEIGHT, "Bouncing Ball");

  while (running) {
    // If the user interacts
    if (gfx_event_waiting()) {
      // Get the interaction
      c = gfx_wait();
      switch (c) {
      case 1:
	// If they click, generate new velocities and set the ball's position to the mouse's position
	gen_velocity(&vx, &vy);
	ballx = gfx_xpos();
	bally = gfx_ypos();
	break;
      case 'q':
	// If they press q, quit the program
	running = 0;
	break;
      default:
	break;
      }
    }
    // Move the ball
    move_ball(&ballx, &bally, &vx, &vy);
    
    // Flush changes to the screen
    gfx_flush();

    // Wait before continuing loop
    usleep(7500);
  }

}

void gen_velocity(int *vx, int *vy) {
  // Generate velocity between 0 and 5
  *vx = rand() % 5 + 1;
  *vy = rand() % 5 + 1;

  // Randomly generate negative velocity
  int which_neg = rand() % 3;
  if (which_neg == 1) {
    *vx *= -1;
  } else if (which_neg == 2) {
    *vy *= -1;
  } else if (which_neg == 3) {
    *vx *= -1;
    *vy *= -1;
  }
  
}

void move_ball(int *px, int *py, int *vx, int *vy) {
  // Clear the screen
  gfx_clear();

  // Test whether the ball will intersect with a border
  test_bounds(px, py, vx, vy);

  // Move the ball
  *px += *vx;
  *py += *vy;

  // Redraw the ball
  gfx_circle(*px, *py, BALL_RADIUS);
  
}

void test_bounds(int *px, int *py, int *vx, int *vy) {
  // Test right and left borders
  if (*px + *vx - BALL_RADIUS <= 0) {
    // If the ball will hit/intersect the right or left, switch its x velocity sign so it "bounces" and place inside boundaries to avoid getting stuck
    *vx *= -1;
    *px = BALL_RADIUS + 1;
  } else if (*px + *vx + BALL_RADIUS >= WIN_WIDTH) {
    // If the ball will hit/intersect the right or left, switch its x velocity sign so it "bounces" and place inside boundaries to avoid getting stuck
    *vx *= -1;
    *px = WIN_WIDTH - BALL_RADIUS - 1;
  }

  // Test top and bottom borders
  if (*py + *vy - BALL_RADIUS <= 0) {
    // If the ball will hit/intersect the top or bottom, switch its y velocity sign so it "bounces"
    *vy *= -1;
    *py = BALL_RADIUS + 1;
  } else if (*py + *vy + BALL_RADIUS >= WIN_HEIGHT) {
    // If the ball will hit/intersect the top or bottom, switch its y velocity sign so it "bounces"
    *vy *= -1;
    *py = WIN_HEIGHT - BALL_RADIUS - 1;
  }
}
