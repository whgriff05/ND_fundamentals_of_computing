// Name: projectfunc.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 11 Function File
// Description: Mini Final Project
#include "projectfunc.h"

void stringify(char str[], int length) {
  str[length - 1] = '\0';
}

void bordered_rectangle(int x, int y, int w, int h, int pad, Color border, Color inside) {
  gfx_color(border.r, border.g, border.b);
  gfx_fill_rectangle(x, y, w, h);

  gfx_color(inside.r, inside.g, inside.b);
  gfx_fill_rectangle(x + pad, y + pad, w - (2 * pad), h - (2 * pad));
}

void bordered_square_radius(LetterSquare s) {
  bordered_rectangle(s.cx - s.rad, s.cy - s.rad, 2 * s.rad, 2 * s.rad, s.pad, s.border, s.inside);
}

    FILE* open_file(int current_file) {
    char filename[20];
    sprintf(filename, "word_files/%d.word", current_file);
    FILE *fp = fopen(filename, "r");

    return fp;
  }

Puzzle open_puzzle(FILE* file) {
  Puzzle output;

  fscanf(file, "%c", &output.central);
  fscanf(file, "%s", output.letters);
  
  int count = 0;
  while (1) {
    fscanf(file, "%s", output.answers[count]);

    count++;

    if (feof(file)) break;
  }
  output.answer_count = count;
  output.amount_found = 0;

  return output;
}

void init_play_letters(Puzzle puzzle, LetterSquare play_letters[]) {
  // Middle square
  play_letters[0].letter = puzzle.central;
  play_letters[0].cx = WIN_WIDTH / 2;
  play_letters[0].cy = WIN_HEIGHT / 2 + 20;
  play_letters[0].rad = 20;
  play_letters[0].pad = 5;

  // External squares
  for (int i = 0; i < MAX_PUZZLE - 1; i++) {
    play_letters[i + 1].letter = puzzle.letters[i];
    play_letters[i + 1].cx = (WIN_WIDTH / 2) + 75 * cos(M_PI / 3 * i);
    play_letters[i + 1].cy = (WIN_HEIGHT / 2 + 20) + 75 * sin(M_PI / 3 * i);
    play_letters[i + 1].rad = 20;
    play_letters[i + 1].pad = 5;
  }
    
}

void init_answer_letters(LetterSquare answer_letters[]) {
  for (int i = 0; i < 10; i++) {
    answer_letters[i].letter = ' ';
    answer_letters[i].cx = 180 + 50 * i;
    answer_letters[i].cy = 85;
    answer_letters[i].rad = 20;
    answer_letters[i].pad = 5;
  }
}

int get_clicked_square(LetterSquare play_letters[], LetterSquare submit, LetterSquare clear, LetterSquare give_up) {
  int xpos = gfx_xpos();
  int ypos = gfx_ypos();
  for (int i = 0; i < MAX_PUZZLE; i++) {
    if (xpos >= play_letters[i].cx - play_letters[i].rad && xpos <= play_letters[i].cx + play_letters[i].rad) {
      if (ypos >= play_letters[i].cy - play_letters[i].rad && ypos <= play_letters[i].cy + play_letters[i].rad) {
	return i;
      }
    }
  }
  if (xpos >= submit.cx - submit.rad && xpos <= submit.cx + submit.rad) {
    if (ypos >= submit.cy - submit.rad && ypos <= submit.cy + submit.rad) {
      return 10;
    }
  }
  if (xpos >= clear.cx - clear.rad && xpos <= clear.cx + clear.rad) {
    if (ypos >= clear.cy - clear.rad && ypos <= clear.cy + clear.rad) {
      return 20;
    }
  }
  if (xpos >= give_up.cx - give_up.rad && xpos <= give_up.cx + give_up.rad) {
    if (ypos >= give_up.cy - give_up.rad && ypos <= give_up.cy + give_up.rad) {
      return 30;
    }
  }
  return -1;
}

int check_answer(LetterSquare answer_letters[], Puzzle *puzzle) {
  char word[11];
  for (int i = 0; i < 10; i++) {
    if (answer_letters[i].letter == ' ') {
      word[i] = '\0';
      break;
    }
    word[i] = answer_letters[i].letter;
  }

  for (int i = 0; i < puzzle->answer_count; i++) {
    if (!strcmp(puzzle->answers[i], word)) {
      for (int j = 0; j < puzzle->amount_found; j++) {
	printf("%d - %d\n", puzzle->already_found[j], i);
	if (puzzle->already_found[j] == i) return -2;
      }
      puzzle->already_found[puzzle->amount_found] = i;
      puzzle->amount_found++;
      return i;
    }
  }
  return -1;
}

void display_end_puzzle(Puzzle current_puzzle, int current_file, Color border, Color inside) {
  bordered_rectangle(50, 50, WIN_WIDTH - 100, WIN_HEIGHT - 100, 10, border, inside);

  char results_text_puzzle[100];
  char results_text_1[100];
  char results_text_2[100];
  float perc = (float) current_puzzle.amount_found / (float) current_puzzle.answer_count * 100;

  sprintf(results_text_puzzle, "Puzzle %d/%d", current_file, MAX_FILE);
  sprintf(results_text_1, "You correctly found %d words!", current_puzzle.amount_found);
  sprintf(results_text_2, "You solved %.2f%% of the puzzle", perc);
      
  gfx_color(0, 0, 0);
  gfx_text(385, WIN_HEIGHT / 2 - 20, results_text_puzzle);
  gfx_text(325, WIN_HEIGHT / 2, results_text_1);
  gfx_text(320, WIN_HEIGHT / 2 + 20, results_text_2);
  if (current_file != MAX_FILE) {
    gfx_text(335, WIN_HEIGHT / 2 + 40, "Press any key to continue");    
  } else {
    gfx_text(350, WIN_HEIGHT / 2 + 40, "Press any key to quit");    
  }
}
