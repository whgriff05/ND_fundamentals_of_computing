// Name: project.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 11 Main Driver
// Description: Mini Final Project
#include "projectfunc.h"

int main() {

  // Variables
  int current_file = 1;
  int running = 1;

  char event;

  ProjectScreen current_screen = STARTING;

  Puzzle current_puzzle;

  FILE *file;

  Color inside_yellow = {240, 182, 48};
  Color inside_grey = {242, 241, 237};
  Color border = {0, 0, 0};

  LetterSquare play_letters[MAX_PUZZLE];
  LetterSquare answer_letters[10];


  // Open the file
  file = open_file(current_file);
  if (!file) {
    printf("Error: word file %d.word not found", current_file);
    return 1;
  }

  // Read the puzzle
  current_puzzle = open_puzzle(file);

  // Open the window and initial setup
  gfx_open(WIN_WIDTH, WIN_HEIGHT, "Spelling Bee");
  gfx_clear_color(255, 255, 255);
  gfx_clear();
  init_play_letters(current_puzzle, play_letters);
  play_letters[0].border = border;
  play_letters[0].inside = inside_yellow;
  for (int i = 1; i < MAX_PUZZLE; i++) {
    play_letters[i].border = border;
    play_letters[i].inside = inside_grey;
  }
  init_answer_letters(answer_letters);
  for (int i = 0; i < 10; i++) {
    answer_letters[i].border = border;
    answer_letters[i].inside = inside_grey;
  }
  

  while (running) {
    gfx_clear();
    switch (current_screen) {
    case STARTING:
      bordered_rectangle(50, 50, WIN_WIDTH - 100, WIN_HEIGHT - 100, 10, border, inside_yellow);

      gfx_color(0, 0, 0);
      gfx_text(330, WIN_HEIGHT / 2, "Welcome to Spelling Bee!");
      gfx_text(325, WIN_HEIGHT / 2 + 20, "Press any key to continue");
      
      gfx_flush();
      gfx_wait();
      current_screen = PLAY;
      break;
    case PLAY:
      for (int i = 0; i < MAX_PUZZLE; i++) {
	bordered_square_radius(play_letters[i]);
	gfx_color(0, 0, 0);
	gfx_text(play_letters[i].cx - 2, play_letters[i].cy + 2, &play_letters[i].letter);
      }
      for (int i = 0; i < 10; i++) {
	bordered_square_radius(answer_letters[i]);
      }
      
      gfx_flush();
      event = gfx_wait();
      if (event == 1) {
	int clicked_square = get_clicked_square(play_letters);
	if (clicked_square == -1) break;
	printf("%d - %c\n", clicked_square, play_letters[clicked_square].letter);
      }
      break;
      
    default:
      break;
    }
    
  }
  
  
  

	return 0;
}
