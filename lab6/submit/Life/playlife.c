// Name: playlife.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 6 Part 1 Main File
// Description: Conway's Game of Life
#include "lifefunc.h"

int main(int argc, char *argv[]) {

  // Variables
  char current_state[MAX_DIMENSION][MAX_DIMENSION];
  char future_state[MAX_DIMENSION][MAX_DIMENSION];

  FILE *fp;

  int cmd = 0;

  // Initial clears to set up the boards with a 40x40 of blanks
  clear_board(current_state);
  clear_board(future_state);

  // if ./playlife is called
  if (argc == 1) {
    // Print a blank board
    print_board(current_state);
    while (cmd == 0) {
      // Ask for command
      cmd = get_command(current_state, future_state);
      print_board(current_state);
    }
    // If the quit command is called
    if (cmd == 1) {
      printf("Goodbye!\n");
      // End the program
      return 0;
    }
    // If the play command is called
    else if (cmd == 2) {
      while (1) {
	// Loop of cycle to the next state, print the board, and wait 0.5 sec
	cycle(current_state, future_state);
	print_board(current_state);
	usleep(PLAY_SPEED);
      }
    }
  }
  // If ./playlife file.ext is called
  else if (argc == 2) {
    // Try to open the file, end the program with an error if none is found
    fp = fopen(argv[1], "r");
    if (!fp) {
      printf("Error: file %s not found\n", argv[1]);
      return 1;
    }

    // Read the commands from the file
    cmd = read_commands(current_state, future_state, fp);
    // If the play command is called
    if (cmd == 1) {
      // Print the first state of the board and wait 0.5 sec before starting the play loop
      print_board(current_state);
      usleep(PLAY_SPEED);
      while (1) {
	// Loop of cycle to the next state, print the board, and wait 0.5 sec
	cycle(current_state, future_state);
	print_board(current_state);
	usleep(PLAY_SPEED);
      }
    } else if (cmd == 2) {
      // If an unknown command is read, end the program
      return 1;
    } else if (cmd == 3) {
      // If the added point is out of bounds
      printf("Point added was out of bounds (min: 0, max: %d)\n", MAX_DIMENSION - 1);
      return 1;
    } else {
      // If no play command is in the file
      printf("No play command in the file. Add a 'p' at the end of the file.\n");
      return 1;
    }
  }
  // If ./playlife x y is called (i.e. more than just ./playlife file.ext)
  else {
    // Print an error and end the program
    printf("Error: too many arguments provided\n");
    return 1;
  }

  return 0;
}
