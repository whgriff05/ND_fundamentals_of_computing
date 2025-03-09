// Name: lifefunc.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 6 Part 1 Function File
// Description: Conway's Game of Life
#include "lifefunc.h"

void clear_board(char board[][MAX_DIMENSION]) {
  // Loops through every index in board setting it to a space character
  for (int i = 0; i < MAX_DIMENSION; i++) {
    for (int j = 0; j < MAX_DIMENSION; j++) {
      board[i][j] = ' ';
    }
  }
}

void copy_board(char initial[][MAX_DIMENSION], char final[][MAX_DIMENSION]) {
  // Loops through every index on the initial board and sets the corresponding final index to the value
  for (int r = 0; r < MAX_DIMENSION; r++) {
    for (int c = 0; c < MAX_DIMENSION; c++) {
      final[r][c] = initial[r][c];
    }
  }
}

void print_board(char board[][MAX_DIMENSION]) {
  // Clears the terminal
  system("clear");
  // Prints a top border line
  for (int i = 0; i < MAX_DIMENSION + 2; i++) {
    printf("-");
  }
  printf("\n");
  // Prints the left wall, the values for the row, and the right wall
  for (int i = 0; i < MAX_DIMENSION; i++) {
    for (int j = -1; j <= MAX_DIMENSION; j++) {
      if (j == -1 || j == MAX_DIMENSION) {
	printf("|");
      } else {
	printf("%c", board[i][j]);
      }
    }
    printf("\n");
  }
  // Prints a bottom border line
  for (int i = 0; i < MAX_DIMENSION + 2; i++) {
    printf("-");
  }
  printf("\n");
}

int get_command(char board[][MAX_DIMENSION], char new_board[][MAX_DIMENSION]) {
  char option;
  int output = 0;
  int row, col;

  // Prints a command icon and gets the command character
  printf(" > ");
  scanf(" %c", &option);

  if (option == 'a') {
    // Scans the next two numbers
    scanf("%d %d", &row, &col);
    // Ensures the board spot exists (row/col are both between 0 and MAX_DIMENSION - 1)
    if (row >= MAX_DIMENSION || row < 0 || col < 0 || col >= MAX_DIMENSION) {
      // Prints out an error and asks the user for a new command
      printf("Error: out of bounds (min: 0, max: %d)\n", MAX_DIMENSION - 1);
      output = get_command(board, new_board);
    } else {
      // Adds the live cell at that spot
      add_live(board, row, col);
      output = 0;
    }
  } else if (option == 'r') {
    // Scans the next two numbers
    scanf("%d %d", &row, &col);
    // Ensures the board spot exists (row/col are both between 0 and MAX_DIMENSION - 1)
    if (row >= MAX_DIMENSION || row < 0 || col < 0 || col >= MAX_DIMENSION) {
      // Prints out an error and asks the user for a new command
      printf("Error: out of bounds (min: 0, max: %d)\n", MAX_DIMENSION - 1);
      output = get_command(board, new_board);
    } else {
      // Removes the live cell at that spot
      remove_live(board, row, col);
      output = 0;
    }
  } else if (option == 'n') {
    // Cycles the evolution by one generation
    cycle(board, new_board);
  } else if (option == 'q') {
    // Returns 1 so main can quit the program
    return 1;
  } else if (option == 'p') {
    // Returns 2 so main can start the play loop
    return 2;
  } else {
    // Prints an error message stating there was an unknown command
    printf("Error: unknown command %c\n", option);
    // Calls the function again to get the correct command
    output = get_command(board, new_board);
  }
  return output;
}

int read_commands(char board[][MAX_DIMENSION], char new_board[][MAX_DIMENSION], FILE *fp) {
  char option;

  // Goes until the end of file is met
  while (!feof(fp)) {
    // Scans the command
    fscanf(fp, "%c", &option);
    if (option == 'a') {
      int row, col;
      // Scans the row and column of the point
      fscanf(fp, "%d %d", &row, &col);
      // Ensures the board spot exists (row/col are both between 0 and MAX_DIMENSION - 1)
      if (row >= MAX_DIMENSION || row < 0 || col < 0 || col >= MAX_DIMENSION) {
	// Prints out an error and ends the program
	printf("Error: out of bounds (min: 0, max: %d)\n", MAX_DIMENSION - 1);
	return 3;
      } else {
	// Adds the live cell at that spot
	add_live(board, row, col);
      }
    } else if (option == 'p') {
      // Returns 1 to start the play loop
      fclose(fp);
      return 1;
    } else if (option == ' ' || option == '\n') {
      // Ignores whitespace or newlines
      continue;
    } else {
      // Prints an error if an unknown command is found and returns 2 for main to end the program
      printf("Error: unknown command %c %d\n", option);
      return 2;
    }
  }
  // If the file gets completely read and no 'p' is found, returns 0 so main can alert the user to add a 'p' at the end
  return 0;
}

void add_live(char board[][MAX_DIMENSION], int row, int col) {
  // Sets the point on the board to X (alive)
  board[row][col] = 'X';
}

void remove_live(char board[][MAX_DIMENSION], int row, int col) {
  // Sets the point on the board to ' ' (dead)
  board[row][col] = ' ';
}

int collect_neighbors(char board[][MAX_DIMENSION], int row, int col) {
  int live = 0;
  // live += board[r][c] / 88 checks if X is present at that spot (X has ASCII code of 88)
  
  // If along the top edge
  if (row == 0) {
    // If in the top left corner
    if (col == 0) {
      live += board[0][1] / 88;
      live += board[1][0] / 88;
      live += board[1][1] / 88;
    }
    // If in the top right corner
    else if (col == MAX_DIMENSION - 1) {
      live += board[0][MAX_DIMENSION - 2] / 88;
      live += board[1][MAX_DIMENSION - 1] / 88;
      live += board[1][MAX_DIMENSION - 2] / 88;
    } else {
      live += board[0][col - 1] / 88;
      live += board[0][col + 1] / 88;
      live += board[1][col - 1] / 88;
      live += board[1][col] / 88;
      live += board[1][col + 1] / 88;
    }
  }
  // If along the bottom edge
  else if (row == MAX_DIMENSION - 1) {
    // If in the bottom left corner
    if (col == 0) {
      live += board[MAX_DIMENSION - 2][0] / 88;
      live += board[MAX_DIMENSION - 2][1] / 88;
      live += board[MAX_DIMENSION - 1][1] / 88;
    }
    // If in the bottom right corner
    else if (col == MAX_DIMENSION - 1) {
      live += board[MAX_DIMENSION - 1][MAX_DIMENSION - 2] / 88;
      live += board[MAX_DIMENSION - 2][MAX_DIMENSION - 2] / 88;
      live += board[MAX_DIMENSION - 2][MAX_DIMENSION - 1] / 88;
    } else {
      live += board[MAX_DIMENSION - 1][col - 1] / 88;
      live += board[MAX_DIMENSION - 1][col + 1] / 88;
      live += board[MAX_DIMENSION - 2][col - 1] / 88;
      live += board[MAX_DIMENSION - 2][col] / 88;
      live += board[MAX_DIMENSION - 2][col + 1] / 88;
    }
  }
  // If along the left edge
  else if (col == 0) {
    live += board[row - 1][0] / 88;
    live += board[row + 1][0] / 88;
    live += board[row - 1][1] / 88;
    live += board[row][1] / 88;
    live += board[row + 1][1] / 88;
  }
  // If along the right edge
  else if (col == MAX_DIMENSION - 1) {
    live += board[row - 1][MAX_DIMENSION - 1] / 88;
    live += board[row + 1][MAX_DIMENSION - 1] / 88;
    live += board[row - 1][MAX_DIMENSION - 2] / 88;
    live += board[row][MAX_DIMENSION - 2] / 88;
    live += board[row + 1][MAX_DIMENSION - 2] / 88;
  }
  // If inside the grid (not along the edges)
  else {
    live += board[row - 1][col - 1] / 88;
    live += board[row - 1][col] / 88;
    live += board[row - 1][col + 1] / 88;
    live += board[row][col - 1] / 88;
    live += board[row][col + 1] / 88;
    live += board[row + 1][col - 1] / 88;
    live += board[row + 1][col] / 88;
    live += board[row + 1][col + 1] / 88;
  }

  return live;
}

void cycle(char board[][MAX_DIMENSION], char new_board[][MAX_DIMENSION]) {
  // Loops through every point along the board
  for (int r = 0; r < MAX_DIMENSION - 1; r++) {
    for (int c = 0; c < MAX_DIMENSION - 1; c++) {
      // Counts the number of live neighbors
      int live = collect_neighbors(board, r, c);
      if (board[r][c] == 'X') {
	// If the current spot is alive and has 2/3 alive neighbors, keep it alive on the new board
	if (live == 3 || live == 2) {
	  add_live(new_board, r, c);
	} else {
	  // Otherwise, kill it on the new board
	  remove_live(new_board, r, c);
	}
      }
      // If the current spot is dead and has 3 alive neighbors, make it alive on the new board
      else {
	if (live == 3) {
	  add_live(new_board, r, c);
	}
      }
    }
  }
  // Copy the new future state board to the current board
  copy_board(new_board, board);
}
