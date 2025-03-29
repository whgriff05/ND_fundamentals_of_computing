#include "crossfunc.h"

int main(int argc, char *argv[]) {
  char board[BOARD_SIZE][BOARD_SIZE];
  init_board(board);
  
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
    input = fopen(argv[1], "r");
    if (!input) {
      printf("Error: file %s not found\n", argv[1]);
      return -1;
    } 
    word_count = get_words(input, words);
  } else if (argc == 3) {
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if (!input) {
      printf("Error: file %s not found\n", argv[1]);
      return -1;
    }
    if (!output) {
      printf("Error: file %s not found\n", argv[2]);
      return -1;
    } 
    word_count = get_words(input, words);
  } else {
    printf("Error: too many arguments\n");
    printf("Usage: ./runcrossword\n");
    printf("       ./runcrossword <input file>\n");
    printf("       ./runcrossword <input file> <output file>\n");
    return -1;
  }

  // Sort the words in descending order
  sort(words, word_count);

  

  /*
  // Place words
  Word placed_words[MAX_WORDS];
  int placed_word_count;
  placed_word_count = place_words(board, wp, word_count, placed_words);
  */

  // Place the first word
  // Calculate starting positions
  wp->posr = (BOARD_SIZE / 2);
  wp->posc = (BOARD_SIZE / 2) - (wp->length / 2);
  wp->orientation = 'h';

  // Place the word
  hplace(board, wp);
  wp++;

  Letter letter = get_intersection(board, wp, 1);

  if (letter.letter == '!') {
    printf("Unable to place word %s\n", wp->word);
  }
  wp->posr = letter.intersect->posr - letter.offset_current;
  wp->posc = letter.intersect->posc + letter.offset_intersect;
  wp->orientation = 'v';
  vplace(board, wp);
    
  
  // Generate clues
  Clue clues[word_count];
  // Put solutions and positions into each clue
  for (int i = 0; i < word_count; i++) {
    strcpy(clues[i].sol, words[i].word);
    clues[i].posr = words[i].posr;
    clues[i].posc = words[i].posc;
    clues[i].orientation = words[i].orientation;
  }
  generate_anagrams(clues, word_count);

  // Display boards
  display_boards(output, board);

  // Display clues
  display_clues(output, clues, word_count);

  return 0;
}
