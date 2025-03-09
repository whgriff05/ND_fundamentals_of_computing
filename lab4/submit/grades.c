// Name: grades.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 4 Part 1
// Description: A Simple Array

#include <stdio.h>
#include <math.h>

// function prototypes ...
float average(int[], int);
float std_dev(int[], int, float);

int main()
{
  int grades[] =
    { 96,73,62,87,80,63,93,79,71,99,
      82,83,80,97,89,82,93,92,95,89,
      71,97,91,95,63,81,76,98,64,86,
      74,79,98,82,77,68,87,70,75,97,
      71,94,68,87,79 };

  int grades_size = sizeof(grades)/sizeof(grades[0]);

  float grades_average = average(grades, grades_size);
  float grades_std_dev = std_dev(grades, grades_size, grades_average);
  printf("Average: %.2f | Standard Deviation: %.2f\n", grades_average, grades_std_dev);
  


  
  return 0;
}

// function definitions ...
float average(int arr[], int size) {
  float total = 0;
  for (int i = 0; i < size; i++) {
    total += arr[i];
  }
  return total / size;
}

float std_dev(int arr[], int size, float avg) {
  float numerator = 0;
  for (int i = 0; i < size; i++) {
    numerator += pow((arr[i] - avg), 2);
  }
  return sqrt(numerator / size);
}
