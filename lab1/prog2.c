// Name: prog2.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 1 Part 2
// Description: Cross Product Calculator
#include <math.h>
#include <stdio.h>

int main() {
  // Variables for components of a and b
  int ax;
  int ay;
  int az;
  int bx;
  int by;
  int bz;

  // Get components of a from user
  printf("X component of a: ");
  scanf ("%d",&ax);
  printf("Y component of a: ");
  scanf ("%d",&ay);
  printf("Z component of a: ");
  scanf ("%d",&az);

  // Get components of b from user
  printf("X component of b: ");
  scanf ("%d",&bx);
  printf("Y component of b: ");
  scanf ("%d",&by);
  printf("Z component of b: ");
  scanf ("%d",&bz);

  // Declare and calculate components of the cross product vector
  int cx = (ay * bz) - (az * by);
  int cy = (az * bx) - (ax * bz);
  int cz = (ax * by) - (ay * bx);
  // Calculuate magnitude of cross product 
  float mag = sqrt((cx * cx) + (cy * cy) + (cz * cz));
  int radicand = (cx * cx) + (cy * cy) + (cz * cz);

  // Display cross product and magnitude to the user
  printf("Cross product of a and b is: <%d, %d, %d>\n", cx, cy, cz);
  printf("Magnitude of the cross product is: %f or sqrt(%d)\n", mag, radicand);
  
  

  
  return 0;
}
