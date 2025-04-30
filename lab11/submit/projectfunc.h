// Name: projectfunc.h
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 11 Header File
// Description: Mini Final Project
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "gfx.h"

// Global Variables
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAX_PUZZLE 7
#define MAX_ANSWERS 50
#define MAX_LETTERS_ANSWER 20


// Structs
typedef struct {
  char central;
  char letters[MAX_PUZZLE];
  char answers[MAX_ANSWERS][MAX_LETTERS_ANSWER];
  int answer_count;
} Puzzle;
typedef struct {
  int r;
  int g;
  int b;
} Color;
typedef struct {
  char letter;
  int cx;
  int cy;
  int rad;
  int pad;
  Color border;
  Color inside;
} LetterSquare;


// Enums
typedef enum {
  STARTING,
  PLAY,
  IN_BETWEEN,
  END
} ProjectScreen;

// Function Prototypes
void stringify(char str[], int length);


void bordered_rectangle(int x, int y, int w, int h, int pad, Color border, Color inside);
void bordered_square_radius(LetterSquare s);

FILE* open_file(int current_file);
Puzzle open_puzzle(FILE* file);
void init_play_letters(Puzzle puzzle, LetterSquare play_letters[]);
void init_answer_letters(LetterSquare answer_letters[]);
int get_clicked_square(LetterSquare play_letters[]);
