// Name: path.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 7 Part 1 Driver
// Description: Path Distance
#include "pathfunc.h"

int main(int argc, char *argv[]) {

  // Variables
  Point points[30];
  FILE *fp;
  int count;

  // Depending on whether file is input with command line arguments or not
  if (argc == 1) {
    // Read a filename from the user
    char filename[50];
    printf("Enter a points file to be read: ");
    scanf("%s", filename);
    // Attempt to open the file
    fp = fopen(filename, "r");
    if (!fp) {
      // If it doesn't exist, quit the program
      printf("Error: file %s not found", filename);
      return 1;
    }
  } else if (argc == 2) {
    // Attempt to open the file
    fp = fopen(argv[1], "r");
    if (!fp) {
      // If it doesn't exist, quit the program
      printf("Error: file %s not found", argv[1]);
      return 1;
    }
  } else {
    // Quit the program if too many command line arguments are added
    printf("Improper argument use. Use ./runpath or ./runpath <file>\n");
    return 1;
  }


  // Read in the points and get the count of them
  count = read_points(fp, points);

  // Display the points
  print_points(points, count);

  return 0;
}
