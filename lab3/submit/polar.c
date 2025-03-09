// Name: polar.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 3 Part 2
// Description: Quadrants and Polar Coordinates

#include <math.h>
#include <stdio.h>


// Function prototypes
int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);


int main() {
  // Variables
  double x, y;
  int quadrant;
  double radius;
  double angle;

  // Ask user for x and y coordinates of a point
  printf("Enter the coordinates of a point (x, y): ");
  scanf("%lf %lf", &x, &y);

  // Calculates the respective values for that point's coordinates
  quadrant = get_quadrant(x, y);
  radius = get_radius(x, y);
  angle = get_angle(x, y);

  // Displays the end info to the user
  show_info(quadrant, radius, angle);


  return 0;
}

int get_quadrant(double x, double y) {
  // Determines the quadrant (or whether the point is on an axis) based on the + or - of the x and y coordinates
  if (x > 0) {
    if (y > 0) {
      return 1;
    } else if (y < 0) {
      return 4;
    } else {
      return 0;
    }
  } else if (x < 0) {
    if (y > 0) {
      return 2;
    } else if (y < 0) {
      return 3;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

double get_radius(double x, double y) {
  // Uses the pythagorean theorem to calculate the coordinate's radius
  return sqrt(pow(x, 2) + pow(y, 2));
}

double get_angle(double x, double y) {
  // Uses inverse tangent to calculate the coordinate's angle
  return (atan2(y, x) * 180 / M_PI);
}

void show_info(int quadrant, double radius, double angle) {
  // Prints to the user the quadrant/axis and the polar coordinates of the point
  if (quadrant == 0) {
    printf("This point lies on an axis.\n");
    printf("The point's polar coordinates are (%g, %g°)\n", radius, angle);
  } else {
    printf("This point lies in quadrant %d.\n", quadrant);
    printf("The point's polar coordinates are (%g, %g°)\n", radius, angle);
  }
}

