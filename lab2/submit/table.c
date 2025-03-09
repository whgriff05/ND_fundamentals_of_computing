// Name: table.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 2 Part 1
// Description: Multiplication Table
#include <stdio.h>

int main() {

  int x;
  int y;
  // Get limits of the table from the user
  printf("Enter the limits of the multiplication table:\n");
  printf("x: ");
  scanf("%d", &x);
  printf("y: ");
  scanf("%d", &y);

  // Print X axis
  printf("* |");
  for (int i = 1; i <= x; i++) {
    printf("%5.d", i);
  }
  
  // Print the axis dividing line
  printf("\n---");
  for (int i = 1; i <= x; i++) {
    printf("-----");
  }
  printf("\n");
  
  // Print each y axis line by each value between 1 and y
  for (int j = 1; j <= y; j++) {
    
    // Print the y value
    printf("%2.d|", j);
    
    // Print each product of the corresponding x and y value for that position
    for (int i = 1; i <= x; i++) {
      printf("%5.d", i * j);
    }
    
    // Go to the next line for the next axis to start
    printf("\n");
  }


  return 0;
}
