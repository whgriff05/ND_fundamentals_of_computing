// Name: project.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 11 Main Driver
// Description: Mini Final Project
#include "projectfunc.h"

void fresh_answer(LetterSquare answer[], Color border, Color inside_grey, int *current);

int main() {

  // Variables
  int current_file = 1;
  int running = 1;
  int current_answer_letter = 0;

  char event;
  char prev_output_msg[60] = " ";

  ProjectScreen current_screen = STARTING;

  Puzzle current_puzzle;

  FILE *file;

  Color inside_yellow = {240, 182, 48};
  Color inside_grey = {242, 241, 237};
  Color border = {0, 0, 0};

  LetterSquare play_letters[MAX_PUZZLE];
  LetterSquare answer_letters[10];
  LetterSquare submit;
  LetterSquare clear;
  LetterSquare give_up;


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
  fresh_answer(answer_letters, border, inside_grey, &current_answer_letter);
  submit.cx = WIN_WIDTH / 4 * 3;
  submit.cy = WIN_HEIGHT - 100;
  submit.rad = 30;
  submit.pad = 5;
  submit.border = border;
  submit.inside = inside_yellow;
  
  clear.cx = WIN_WIDTH / 4;
  clear.cy = WIN_HEIGHT - 100;
  clear.rad = 30;
  clear.pad = 5;
  clear.border = border;
  clear.inside = inside_yellow;
  
  give_up.cx = WIN_WIDTH / 4 - 85;
  give_up.cy = WIN_HEIGHT - 100;
  give_up.rad = 30;
  give_up.pad = 5;
  give_up.border = border;
  give_up.inside = inside_yellow;
  

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
	char let[2];
	sprintf(let, "%c", play_letters[i].letter);
	gfx_text(play_letters[i].cx - 2, play_letters[i].cy + 2, let);
      }
      for (int i = 0; i < 10; i++) {
	bordered_square_radius(answer_letters[i]);
	gfx_color(0, 0, 0);
	char let[2];
	sprintf(let, "%c", answer_letters[i].letter);
	gfx_text(answer_letters[i].cx - 2, answer_letters[i].cy + 2, let);
      }
      bordered_square_radius(submit);
      bordered_square_radius(clear);
      bordered_square_radius(give_up);
      gfx_color(0, 0, 0);
      gfx_text(submit.cx - 17, submit.cy + 2, "Submit");
      gfx_text(clear.cx - 15, clear.cy + 2, "Clear");
      gfx_text(give_up.cx - 19, give_up.cy + 2, "Give Up");
      gfx_text(WIN_WIDTH / 2 - 40, 125, prev_output_msg);
      
      gfx_flush();
      event = gfx_wait();
      if (event == 1) {
	int clicked_square = get_clicked_square(play_letters, submit, clear, give_up);
	if (clicked_square == -1) break;
	if (clicked_square >= 0 && clicked_square <= 6) {
	  if (clicked_square == 0) answer_letters[current_answer_letter].inside = inside_yellow;
	  printf("%d - %c\n", clicked_square, play_letters[clicked_square].letter);
	  answer_letters[current_answer_letter].letter = play_letters[clicked_square].letter;
	  current_answer_letter++;
	} else if (clicked_square == 10) {
	  printf("%d - Submit\n", clicked_square);
	  int success = check_answer(answer_letters, &current_puzzle);
	  if (success >= 0) {
	    sprintf(prev_output_msg, "Correct: %s", current_puzzle.answers[success]);
	  } else if (success == -1) {
	    sprintf(prev_output_msg, "Incorrect word");
	  } else if (success == -2) {
	    sprintf(prev_output_msg, "Already submitted");
	  }

	  if (current_puzzle.answer_count == current_puzzle.amount_found) {
	    if (current_file == MAX_FILE) current_screen = END;
	    if (current_file < MAX_FILE) current_screen = IN_BETWEEN;
	  }
	  fresh_answer(answer_letters, border, inside_grey, &current_answer_letter);
	} else if (clicked_square == 20) {
	  printf("%d - Clear\n", clicked_square);
	  fresh_answer(answer_letters, border, inside_grey, &current_answer_letter);
	  sprintf(prev_output_msg, " ");
	} else if (clicked_square == 30) {
	  printf("%d - Give Up\n", clicked_square);
	}

      }
      break;
      
    default:
      break;
    }
    
  }
  
  
  

  return 0;
}


void fresh_answer(LetterSquare answer[], Color border, Color inside_grey, int *current) {
  init_answer_letters(answer);
  for (int i = 0; i < 10; i++) {
    answer[i].border = border;
    answer[i].inside = inside_grey;
  }
  *current = 0;
}
