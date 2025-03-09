// Name: prog1.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 1 Part 1
// Description: Football Score Formula
#include <stdio.h>

int main() {
  // Variables
  int touchdowns;
  int extra_points;
  int field_goals;
  int safeties;
  int total;

  // User input for number of scores
  printf("Number of touchdowns: ");
  scanf ("%d",&touchdowns);
  printf("Number of extra points: ");
  scanf ("%d",&extra_points);
  printf("Number of field goals: ");
  scanf ("%d",&field_goals);
  printf("Number of safeties: ");
  scanf ("%d",&safeties);

  // Calcluates total points
  total = touchdowns * 6 + extra_points + field_goals * 3 + safeties * 2;

  // Tells the user total points
  printf("Number of total points: %d\n", total);
  
  return 0;
}
