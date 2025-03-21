// Name: pathfunc.h
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 7 Part 1 Header File
// Description: Path Distance
#include <math.h>
#include <stdio.h>


// Structs

typedef struct {
  float x;
  float y;
} Point;

// Function Prototypes
int read_points(FILE*, Point[]);
void print_points(Point[], int);
float calculate_distance(Point[], int);
