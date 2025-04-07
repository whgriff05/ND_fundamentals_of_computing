#include "crossfunc.h"

int main(int argc, char *argv[]) {
  // Initialize Variables
  char board[BOARD_SIZE][BOARD_SIZE];
  init_board(board); // Fill a blank board
  
  int word_count;
  
  Word words[MAX_WORDS];
  Word *wp = words;

  FILE *input = stdin;
  FILE *output = stdout;

  if (argc == 1) {
    // Get words and word count from user
    printf("Please enter up to 20 words followed by a '.'\n");
    word_count = get_words(input, words);
  } else if (argc == 2) {
    // Set the input file pointer to the input file
    input = fopen(argv[1], "r");
    // Check if the file exists
    if (!input) {
      printf("Error: file %s not found\n", argv[1]);
      return -1;
    }
    // Get words and word count
    word_count = get_words(input, words);
  } else if (argc == 3) {
    // Set the input and output file pointers
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    // Check if the files exist
    if (!input) {
      printf("Error: file %s not found\n", argv[1]);
      return -1;
    }
    if (!output) {
      printf("Error: file %s not found\n", argv[2]);
      return -1;
    }
    // Get words and word count
    word_count = get_words(input, words);
  } else {
    // Tell the user how to run the program
    printf("Error: too many arguments\n");
    printf("Usage: ./runcrossword\n");
    printf("       ./runcrossword <input file>\n");
    printf("       ./runcrossword <input file> <output file>\n");
    return -1;
  }

  // Sort the words in descending order
  sort(words, word_count);

  // Place words
  Word placed_words[MAX_WORDS];
  int placed_word_count = 0;
  int previous_pwc = placed_word_count;
  placed_word_count = place_words(board, wp, word_count, placed_words, placed_word_count);

  // Continue placing words until no more words can be placed
  while (previous_pwc != placed_word_count) {
    placed_word_count += place_words(board, wp, word_count, placed_words, placed_word_count);
    previous_pwc = placed_word_count;
  }


  Clue clues[placed_word_count];
  // Put solutions and positions into each clue
  for (int i = 0; i < placed_word_count; i++) {
    strcpy(clues[i].sol, placed_words[i].word);
    clues[i].posr = placed_words[i].posr;
    clues[i].posc = placed_words[i].posc;
    clues[i].orientation = placed_words[i].orientation;
  }
  // Generate clues
  generate_anagrams(clues, placed_word_count);

  printf("\n");
  
  // Warn the user of unplaced words
  int unplaced = 0;
  for (int i = 0; i < word_count; i++) {
    if (words[i].placed == 0) unplaced++; 
  }
  if (unplaced > 0) {
    fprintf(output, "These words were unable to be placed:\n");
    for (int i = 0; i < word_count; i++) {
      if (words[i].placed == 0) fprintf(output, "%s\n", words[i].word);
    }
  }

  printf("\n");

  // Display boards
  display_boards(output, board);

  // Display clues
  display_clues(output, clues, placed_word_count);

  return 0;
}
