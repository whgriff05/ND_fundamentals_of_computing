// Name: usastates.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 7 Part 2 Driver
// Description: US States and Capitals
#include "statesfunc.h"

// Global variable for states array size
const int max_states = 100;

int main(int argc, char *argv[]) {

  // Variables
  int count_states;
  int exit_code;

  State states[max_states];

  char filename[30];
  
  FILE *fp;


  // Determines on whether a file name needs to be asked for based on command line arguments
  if (argc == 1) {
    // Asks for the name of a file
    printf("Enter the name of a states file: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    // Attempts to open the file and exits with an error if no file is found
    if (!fp) {
      printf("Error: file %s not found\n", filename);
      return 1;
    }
  } else if (argc == 2) {
    fp = fopen(argv[1], "r");
    // Attempts to open the file and exits with an error if no file is found
    if (!fp) {
      printf("Error: file %s not found\n", argv[1]);
      return 1;
    }
  } else {
    // If too many arguments are provided, the program exits with instructions on how to run the program
    printf("Error: too many command line arguments\n");
    printf("Usage: ./states\n");
    printf("       ./states <state file>\n");
    return 1;
  }

  // Reads in all the states and gets the count
  count_states = read_states(fp, states);
  
  while (1) {
    // While the program is in the run loop, the user menu is printed, the user makes a decision
    exit_code = user_menu(states, count_states);
    // If -1 is returned (quit), the program will quit with a goodbye message
    if (exit_code == -1) {
      printf("Goodbye\n");
      break;
    }
  }

  return 0;
}
