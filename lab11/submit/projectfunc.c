// Name: projectfunc.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 11 Function File
// Description: Mini Final Project
#include "projectfunc.h"

void bordered_rectangle(int x, int y, int w, int h, int pad, Color border, Color inside) {
  // Create the bigger border rectangle with the border color
  gfx_color(border.r, border.g, border.b);
  gfx_fill_rectangle(x, y, w, h);

  // Create the smaller inner rectangle with the inner color
  gfx_color(inside.r, inside.g, inside.b);
  gfx_fill_rectangle(x + pad, y + pad, w - (2 * pad), h - (2 * pad));
}

void bordered_square_radius(LetterSquare s) {
  // Create a bordered rectangle given the LetterSquare's dimensions and colors
  bordered_rectangle(s.cx - s.rad, s.cy - s.rad, 2 * s.rad, 2 * s.rad, s.pad, s.border, s.inside);
}

FILE* open_file(int current_file) {
  char filename[20];
  // Get the filename from the current file number
  sprintf(filename, "word_files/%d.word", current_file);

  // Open and return the file pointer to the file
  FILE *fp = fopen(filename, "r");

  return fp;
}

Puzzle open_puzzle(FILE* file) {
  Puzzle output;

  // Get the yellow letter and the rest of the play letters from the file
  fscanf(file, "%c", &output.central);
  fscanf(file, "%s", output.letters);
  
  int count = 0;
  while (1) {
    // Get the word
    fscanf(file, "%s", output.answers[count]);

    // Increment the count
    count++;

    // Detect end of file
    if (feof(file)) break;
  }

  // Set the answer count and amount found to their corresponding amounts
  output.answer_count = count;
  output.amount_found = 0;

  return output;
}

void init_play_letters(Puzzle puzzle, LetterSquare play_letters[]) {
  // Middle square
  play_letters[0].letter = puzzle.central; // Set letter
  play_letters[0].cx = WIN_WIDTH / 2; // Set x position
  play_letters[0].cy = WIN_HEIGHT / 2 + 20; // Set y position
  play_letters[0].rad = 20; // Set square radius
  play_letters[0].pad = 5; // Set border padding

  // External squares
  for (int i = 0; i < MAX_PUZZLE - 1; i++) {
    play_letters[i + 1].letter = puzzle.letters[i]; // Set letter
    play_letters[i + 1].cx = (WIN_WIDTH / 2) + 75 * cos(M_PI / 3 * i); // Set x position
    play_letters[i + 1].cy = (WIN_HEIGHT / 2 + 20) + 75 * sin(M_PI / 3 * i); // Set y position
    play_letters[i + 1].rad = 20; // Set square radius
    play_letters[i + 1].pad = 5; // Set border padding
  }
    
}

void init_answer_letters(LetterSquare answer_letters[]) {
  // Sets letter, x and y positions, square radius, and border padding for all answer squares
  for (int i = 0; i < 10; i++) {
    answer_letters[i].letter = ' ';
    answer_letters[i].cx = 180 + 50 * i;
    answer_letters[i].cy = 85;
    answer_letters[i].rad = 20;
    answer_letters[i].pad = 5;
  }
}

int get_clicked_square(LetterSquare play_letters[], LetterSquare submit, LetterSquare clear, LetterSquare give_up) {
  // Gets the mouse coordinates
  int xpos = gfx_xpos();
  int ypos = gfx_ypos();

  // For each button (each playable letter, submit, clear, give up), the mouse position must be between the x and y boundaries of the button for it to count as a click. Each button has a different return code
  
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

  // If no button is clicked, return -1
  return -1;
}

int check_answer(LetterSquare answer_letters[], Puzzle *puzzle) {
  char word[11];
  for (int i = 0; i < 10; i++) {
    // Combine all the answer squares to form the submitted word
    if (answer_letters[i].letter == ' ') {
      word[i] = '\0';
      break;
    }
    word[i] = answer_letters[i].letter;
  }

  
  for (int i = 0; i < puzzle->answer_count; i++) {
    // Check the submitted word against all answers for the puzzle
    if (!strcmp(puzzle->answers[i], word)) {
      // If there is a match, make sure the answer was not already submitted
      for (int j = 0; j < puzzle->amount_found; j++) {
	if (puzzle->already_found[j] == i) return -2;
      }

      // If not already submitted, add to the submission list
      puzzle->already_found[puzzle->amount_found] = i;
      puzzle->amount_found++;
      return i;
    }
  }

  // If not an answer, return -1
  return -1;
}

void display_end_puzzle(Puzzle current_puzzle, int current_file, Color border, Color inside) {
  // Display a rectangle
  bordered_rectangle(50, 50, WIN_WIDTH - 100, WIN_HEIGHT - 100, 10, border, inside);

  char results_text_puzzle[100];
  char results_text_1[100];
  char results_text_2[100];
  float perc = (float) current_puzzle.amount_found / (float) current_puzzle.answer_count * 100; // Calculate % completion of the puzzle

  // Set up the text to display to the user
  sprintf(results_text_puzzle, "Puzzle %d/%d", current_file, MAX_FILE);
  sprintf(results_text_1, "You correctly found %d/%d words!", current_puzzle.amount_found, current_puzzle.answer_count);
  sprintf(results_text_2, "You solved %.2f%% of the puzzle", perc);

  // Print the results text
  gfx_color(0, 0, 0);
  gfx_text(385, WIN_HEIGHT / 2 - 20, results_text_puzzle);
  gfx_text(317, WIN_HEIGHT / 2, results_text_1);
  gfx_text(320, WIN_HEIGHT / 2 + 20, results_text_2);
  if (current_file != MAX_FILE) {
    // Show this to move onto the next puzzle (if one remains)
    gfx_text(335, WIN_HEIGHT / 2 + 40, "Press any key to continue");    
  } else {
    // Show this to quit the program (if no more puzzles remain)
    gfx_text(350, WIN_HEIGHT / 2 + 40, "Press any key to quit");    
  }
}
