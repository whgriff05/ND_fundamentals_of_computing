#include "crossfunc.h"

int is_str_alpha(char str[]) {
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(str[i])) return 0;
  }
  return 1;
}

int get_words(FILE *fp, Word words[]) {
  int count = 0;
  while (1) {
    char current_word[BOARD_SIZE + 1];
    fscanf(fp, "%s", current_word);

    if (feof(fp)) break;

    if (!strcmp(".", current_word)) break;

    if (!is_str_alpha(current_word)) break;

    strcpy(words[count].word, current_word);
    words[count].length = strlen(current_word);

    count++;

    if (count >= 20) break;
  }
  return count;
}

void sort(Word words[], int count) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (words[j].length < words[j+1].length) {
	Word temp = words[j];
	words[j] = words[j+1];
	words[j+1] = temp;
      }
    }
  }
  for (int i = 0; i < count; i++) {
    words[i].order = i;
  }
}

void init_board(char board[][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
}

void hplace(char board[][BOARD_SIZE], Word *wp) {
  for (int i = 0; i < wp->length; i++)
    board[wp->posr][wp->posc + i] = wp->word[i];
}

void display(char board[][BOARD_SIZE]) {
  for (int x = 0; x < BOARD_SIZE + 2; x++) {
    if (x == 0 || x == 16) {
      for (int y = 0; y < BOARD_SIZE + 2; y++) {
	printf("-");
      }
      printf("\n");
    } else {
      printf("|");
      for (int y = 0; y < BOARD_SIZE; y++) {
	printf("%c", board[x-1][y]);
      }
      printf("|\n");
    }
  }
}

void place_words(char board[][BOARD_SIZE], Word *wp, int count) {
  int amt_tried = 0;
  // Check if first word
  if (wp->order == 0) {
    // Calculate starting positions
    wp->posr = (BOARD_SIZE / 2);
    wp->posc = (BOARD_SIZE / 2) - (wp->length / 2);
    wp->orient = 'h';

    // Place the word
    hplace(board, wp);
    
    // Increment the word pointer and the amount tried
    wp++;
    amt_tried++;
  }
  while (amt_tried < count) {
    Letter letter = get_intersection(wp, amt_tried);
  }
  
}

Letter get_intersection(Word *wp, int amt_tried) {
  Letter letter;
  Word *current = wp;

  // Back up word pointer to start of array
  wp -= amt_tried;

  for (int i = 0; i < amt_tried - 1; i++) {
    for (int j = 0; j < current->length; j++) {
      for (int k = 0; k < wp->length; k++) {
	if (current->word[j] == wp->word[k]) {
	  letter.letter = current->word[j];
	  letter.offset_current = j;
	  letter.offset_intersect = k;
	  letter.intersect = wp;
	  return letter;
	}
      }
    }
    wp++;
  }
}
