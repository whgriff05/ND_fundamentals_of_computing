#include "crossfunc.h"

int main(int argc, char *argv[]) {
  char board[BOARD_SIZE][BOARD_SIZE];
  init_board(board);
  
  int word_count;
  
  Word words[MAX_WORDS];
  Word *wp = words;

  FILE *input;
  FILE *output;

  if (argc == 1) {
    // Get words and word count from user
    printf("Please enter up to 20 words followed by a '.'\n");
    word_count = get_words(stdin, words);
  } else if (argc == 2) {
    input = fopen(argv[1], "r");
    if (!input) {
      printf("Error: file %s not found\n", argv[1]);
      return -1;
    } 
    word_count = get_words(input, words);
  } else if (argc == 3) {
    printf("TODO: implement\n");
  } else {
    printf("TODO: implement\n");
    return -1;
  }

  // Sort the words in descending order
  sort(words, word_count);

  // Place words
  Word placed_words[MAX_WORDS];
  int placed_word_count;
  placed_word_count = place_words(board, wp, word_count, placed_words);

  // Generate clues
  Clue clues[placed_word_count];
  // Put solutions and positions into each clue
  for (int i = 0; i < placed_word_count; i++) {
    strcpy(clues[i].sol, placed_words[i].word);
    clues[i].posr = placed_words[i].posr;
    clues[i].posc = placed_words[i].posc;
    clues[i].orientation = placed_words[i].orientation;
  }
  generate_anagrams(clues, placed_word_count);

  // Display boards
  display_boards(board);

  // Display clues
  display_clues(clues, placed_word_count);

  return 0;
}
