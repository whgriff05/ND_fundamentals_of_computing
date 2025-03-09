// Name: lifefunc.h
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 6 Part 1 Header File
// Description: Conway's Game of Life
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Defines the grid size
#define MAX_DIMENSION 40
#define PLAY_SPEED 125000


// Function prototypes
void clear_board(char[][MAX_DIMENSION]);
void copy_board(char[][MAX_DIMENSION], char[][MAX_DIMENSION]);
void print_board(char[][MAX_DIMENSION]);
int get_command(char[][MAX_DIMENSION], char[][MAX_DIMENSION]);
int read_commands(char[][MAX_DIMENSION], char[][MAX_DIMENSION], FILE *);
void add_live(char[][MAX_DIMENSION], int, int);
void remove_live(char[][MAX_DIMENSION], int, int);
int collect_neighbors(char[][MAX_DIMENSION], int, int);
void cycle(char[][MAX_DIMENSION], char[][MAX_DIMENSION]);

