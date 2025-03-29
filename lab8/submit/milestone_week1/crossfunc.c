#include "crossfunc.h"

int is_str_alpha(char str[]) {
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(str[i])) return 0;
  }
  return 1;
}

void to_caps(char str[]) {
  for (int i = 0; i < strlen(str); i++) {
    str[i] = toupper(str[i]);
  }
}

int get_words(FILE *fp, Word words[]) {
  int count = 0;
  while (1) {
    char current_word[BOARD_SIZE + 1];
    fscanf(fp, "%s", current_word);

    if (feof(fp)) break;

    if (!strcmp(".", current_word)) break;

    if (!is_str_alpha(current_word)) {
      printf("Error: %s is not a recognized word\n", current_word);
      continue;
    }

    if (strlen(current_word) > BOARD_SIZE) {
      printf("Error: %s is too long of a word (%d letters max)\n", current_word, BOARD_SIZE);
      continue;
    } else if (strlen(current_word) <= 1) {
      printf("Error: %s is too short of a word (>1 letters min)\n", current_word);
      continue;
    }
    
    to_caps(current_word);
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

void vplace(char board[][BOARD_SIZE], Word *wp) {
  for (int i = 0; i < wp->length; i++)
    board[wp->posr + i][wp->posc] = wp->word[i];
}

void display(FILE *fp, char board[][BOARD_SIZE]) {
  for (int x = 0; x < BOARD_SIZE + 2; x++) {
    if (x == 0 || x == 16) {
      for (int y = 0; y < BOARD_SIZE + 2; y++) {
	fprintf(fp, "-");
      }
      fprintf(fp, "\n");
    } else {
      fprintf(fp, "|");
      for (int y = 0; y < BOARD_SIZE; y++) {
	fprintf(fp, "%c", board[x-1][y]);
      }
      fprintf(fp, "|\n");
    }
  }
}

void display_boards(FILE *fp, char board[][BOARD_SIZE]) {
  char sol_board[BOARD_SIZE][BOARD_SIZE];
  init_board(sol_board);
  char empty_board[BOARD_SIZE][BOARD_SIZE];
  init_board(empty_board);

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
	sol_board[i][j] = '.';
	empty_board[i][j] = '#';
      } else if (isalpha(board[i][j])) {
	sol_board[i][j] = board[i][j];
	empty_board[i][j] = ' ';
      }
    }
  }
  
  fprintf(fp, "SOLUTION:\n");
  display(fp, sol_board);

  fprintf(fp, "\nPUZZLE:\n");
  display(fp, empty_board);
}

void display_clues(FILE *fp, Clue clues[], int placed_word_count) {
  // Print header
  fprintf(fp, "Location | Direction | Anagram\n");
  for (int i = 0; i < placed_word_count; i++) {
    char dir[20];
    if (clues[i].orientation == 'v') {
      strcpy(dir, "Down");
    } else if (clues[i].orientation == 'h') {
      strcpy(dir, "Across");
    }
    fprintf(fp, "%4d,%-4d| %9s | %s\n", clues[i].posr + 1, clues[i].posc + 1, dir, clues[i].anagram);
  }
}

int place_words(char board[][BOARD_SIZE], Word *wp, int count, Word placed_words[]) {
  int amt_tried = 0;
  // Check if first word
  if (wp->order == 0) {
    // Calculate starting positions
    wp->posr = (BOARD_SIZE / 2);
    wp->posc = (BOARD_SIZE / 2) - (wp->length / 2);
    wp->orientation = 'h';

    // Place the word
    hplace(board, wp);

    // Add to record
    placed_words[amt_tried] = *wp;
    
    // Increment the word pointer and the amount tried
    wp++;
    amt_tried++;
  }
  while (amt_tried < count) {
    Letter letter = get_intersection(board, wp, amt_tried);

    if (letter.letter == '!') {
      break;
    }
    
    int posr, posc;
    
    // See if the intersected word is vertical or horizontal
    if (letter.intersect->orientation == 'h') {
      posr = letter.intersect->posr - letter.offset_current;
      posc = letter.intersect->posc + letter.offset_intersect;
      wp->posr = posr;
      wp->posc = posc;
      wp->orientation = 'v';
      vplace(board, wp);
    } else if (letter.intersect->orientation == 'v') {
      posr = letter.intersect->posr + letter.offset_intersect;
      posc = letter.intersect->posc - letter.offset_current;
      wp->posr = posr;
      wp->posc = posc;
      wp->orientation = 'h';
      hplace(board, wp);
    } 
    placed_words[amt_tried] = *wp;
    wp++;
    amt_tried++;
  }

  return amt_tried;
  
}

Letter get_intersection(char board[][BOARD_SIZE], Word *wp, int amt_tried) {
  Letter letter;
  Word *current = wp;
  
  wp--;
  
  for (int i = amt_tried; i > 0; i--) {
    for (int j = 0; j < current->length; j++) {
      for (int k = 0; k < wp->length; k++) {

	if (current->word[j] == wp->word[k]) {
	  letter.letter = current->word[j];
	  letter.offset_current = j;
	  letter.offset_intersect = k;
	  letter.intersect = wp;

	  if (check_pos(board, current, letter)) {
	    return letter;
	  }
	}
      }
    }
    wp--;
  }
  letter.letter = '!';
  return letter;
}

int check_pos(char board[][BOARD_SIZE], Word *current, Letter letter) {
  int startr, endr;
  int startc, endc;
  if (letter.intersect->orientation == 'h') {
    startr = letter.intersect->posr - letter.offset_current - 1;
    endr = startr + current->length + 1;
    startc = letter.intersect->posc + letter.offset_intersect - 1;
    endc = letter.intersect->posc + letter.offset_intersect + 1;
  } else if (letter.intersect->orientation == 'v') {
    startr = letter.intersect->posr + letter.offset_intersect - 1;
    endr = letter.intersect->posr + letter.offset_intersect + 1;
    startc = letter.intersect->posc - letter.offset_current - 1;
    endc = startc + current->length + 1;
  }

  //printf("%s - %c - %s | %d-%d | %d-%d\n", current->word, letter.letter, letter.intersect->word, startr, endr, startc, endc);
  
  if (startc < -1 || endc > BOARD_SIZE || startr < -1 || endr > BOARD_SIZE) {
    //printf("%d %d %d %d\n", startc <= -1, endc > BOARD_SIZE, startr <= -1, endr > BOARD_SIZE);
    return 0;
  }
  
  for (int r = startr; r <= endr; r++) {
    for (int c = startc; c <= endc; c++) {
      if (r < 0 || c < 0 || r >= BOARD_SIZE || c >= BOARD_SIZE) continue;
      if (letter.intersect->orientation == 'h' && r == letter.intersect->posr) continue;
      if (letter.intersect->orientation == 'v' && c == letter.intersect->posc) continue;
      if (board[r][c] != ' ') {
	return 0;
      }
    }
  }
  return 1;
  
}

void generate_anagrams(Clue clues[], int count) {
  for (int i = 0; i < count; i++) {
    char word[BOARD_SIZE + 1];
    strcpy(word, clues[i].sol);
    scramble(word);
    strcpy(clues[i].anagram, word);
  }
}

void scramble(char word[]) {
  int len = strlen(word);
  // Scramble
  srand(time(NULL));
  for (int i = 0; i < len * 2; i++) {
    int i1 = rand() % len;
    int i2 = rand() % len;
    char temp;
    temp = word[i1];
    word[i1] = word[i2];
    word[i2] = temp;
  }
}
