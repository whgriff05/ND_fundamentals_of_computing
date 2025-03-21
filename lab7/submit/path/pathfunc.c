// Name: pathfunc.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 7 Part 1 Functions
// Description: Path Distance
#include "pathfunc.h"

int read_points(FILE *fp, Point p[]) {
  int count = 0;

  while (1) {
    // Scan the points
    fscanf(fp, "%f %f", &p[count].x, &p[count].y);

    // If the end of file is reached, end the reading
    if (feof(fp)) break;

    // Increment the count
    count++;
  }

  // Return the count
  return count;
}

void print_points(Point p[], int count) {
  // Print the start of the grid
  printf("There are %d points\n\n", count);
  printf("   x   |   y   \n");
  printf("-------+-------\n");
  for (int i = 0; i < count; i++) {
    // For each point, print the x & y values
    printf("%7.3g|%7.3g\n", p[i].x, p[i].y);
  }
  // Calculate the distance and print the total distance
  float dist = calculate_distance(p, count);
  printf("The length of the path through these points is: %.4g\n", dist);
}

float calculate_distance(Point p[], int count) {
  float total_dist = 0;
  for (int i = 0; i < count - 1; i++) {
    // Get the x & y components of distance
    float dx = p[i].x - p[i+1].x;
    float dy = p[i].y - p[i+1].y;
    // Get the magnitude of the distance
    float dist = sqrt(pow(dx, 2) + pow(dy, 2));
    // Sum them together for the total distance
    total_dist += dist;
  }
  return total_dist;
}
