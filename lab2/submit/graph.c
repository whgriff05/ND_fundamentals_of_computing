// Name: graph.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 2 Part 3
// Description: ASCII Plot
#include <math.h>
#include <stdio.h>

int main() {

  // Equation: 5 * (sin(x^(1/3)))^2

  // Variables
  int x;
  double y;
  int max_x;
  double max_y;
  int min_x;
  double min_y;

  // Header
  printf("Graph of y = 5 * (sin(x^(1/3)))^2\n from x = 0 to x = 100");
  printf(" X    Y  \n");

  // Loop for 100 values of x				
  for (x = 0; x <= 100; x++) {
    // Calculate y according to the equation
    y = 5 * pow(sin(pow(x, 1./3)), 2);
    // Print the x and y variables to the table
    printf("%-3d %.4lf ", x, y);
    
    // Check for maximum value
    if (y > max_y) {
      max_y = y;
      max_x = x;
    }
    // Check for minimum value
    if (y < min_y) {
      min_y = y;
      min_x = x;
    }
    
    // Print out # proportional to the y value
    for (int i = 0; i < y * 10; i++) {
      printf("#");
    }
    printf("#\n");
  }

  printf("The maximum of %d was at %.4lf\n", max_x, max_y);
  printf("The minimum of %d was at %.4lf\n", min_x, min_y);

  return 0;
}
