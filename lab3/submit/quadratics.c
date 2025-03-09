// Name: quadratics.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 3 Part 1
// Description: Multiple Quadratics
#include <stdio.h>
#include <math.h>

// Function Prototypes
double calculate_disc(double, double, double);

int main()
{
  // Variables
  double a, b, c, disc;
  double x1, x2;

  // Keep looping the roots
  while (1) {
    // Ask the users for coefficients
    printf("Enter the coefficients (a,b,c) of a quadratic equation: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    // if a is 0, break the loop and end the program
    if (!a)
      break;
    printf("\n");

    // Calculate the discriminant
    disc = calculate_disc(a, b, c);

    // Calculate roots depending on sign of discriminant
    if (disc == 0) {
      x1 = (-1 * b) / (2 * a);
      printf("Quadratic equation has one root: %lf\n", x1);
    } else if (disc > 0) {
      x1 = (-1 * b + sqrt(disc)) / (2 * a);
      x2 = (-1 * b - sqrt(disc)) / (2 * a);
      printf("Quadratic equation roots are: %lf and %lf\n", x1, x2);
    } else {
      printf("Quadratic equation has no real solutions.\n");
    }
  }

  return 0;
}

double calculate_disc(double a, double b, double c) {
  // Calculate the discriminant
  return pow(b, 2) - (4 * a * c); 
}

