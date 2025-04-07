#include "crossfunc.h"

int is_str_alpha(char str[]) {
  // See if each character is a-z
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(str[i])) return 0;
  }
  return 1;
}

void to_caps(char str[]) {
  // Set each character to its uppercase variant
  for (int i = 0; i < strlen(str); i++) {
    str[i] = toupper(str[i]);
  }
}

void stringify(char str[]) {
  // Replace newlines with null characters
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '\n') str[i] = '\0';
  }
  
}

int get_words(FILE *fp, Word words[]) {
  int count = 0;
  int overall_count = 1;
  while (1) {
    char current_word[BOARD_SIZE + 1];

    // Take in a word
    fgets(current_word, 16, fp);

    // Convert the \n to \0
    stringify(current_word);
    
    // Make sure word isn't too long
    if (strlen(current_word) >= BOARD_SIZE) {
      if (current_word[strlen(current_word)] != '\n' && fgetc(fp) != '\n') {
	if (feof(fp)) break;
	while (1) {
	  if (fgetc(fp) == '\n') break;
	}
	// If the word is too long, alert the user and ignore it
	printf("Error: Word #%d is too long of a word (%d letters max)\n", overall_count, BOARD_SIZE);
	overall_count++;
	continue;
      }
    }


    // Stop at the end of file
    if (feof(fp)) break;

    // Stop taking in words after a period is entered
    if (!strcmp(".", current_word)) break;

    // If the word is not only a-z, alert the user and ignore it
    if (!is_str_alpha(current_word)) {
      printf("Error: Word #%d is not a recognized word (only use A-Z)\n", overall_count);
      overall_count++;
      continue;
    }

    // If the word is only one letter long, alert the user and ignore it
    if (strlen(current_word) <= 1) {
      printf("Error: Word #%d is too short of a word (>1 letters min)\n", overall_count);
      overall_count++;
      continue;
    }

    // Convert the word to caps
    to_caps(current_word);

    // Add the word's information to the list of words
    strcpy(words[count].word, current_word);
    words[count].length = strlen(current_word);
    words[count].placed = 0;

    // Increase the word counts
    overall_count++;
    count++;

    // Stop the word intake if 20 words are given
    if (count >= 20) break;
  }
  return count;
}

void sort(Word words[], int count) {
  // Use the bubble sort algorithm to sort the words in descending length order
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (words[j].length < words[j+1].length) {
	Word temp = words[j];
	words[j] = words[j+1];
	words[j+1] = temp;
      }
    }
  }
  // Give the words their order
  for (int i = 0; i < count; i++) {
    words[i].order = i;
  }
}

void init_board(char board[][BOARD_SIZE]) {
  // Fill the board with blank spaces
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
}

void hplace(char board[][BOARD_SIZE], Word *wp) {
  // Place the word's letters horizontally across the board array
  for (int i = 0; i < wp->length; i++)
    board[wp->posr][wp->posc + i] = wp->word[i];
}

void vplace(char board[][BOARD_SIZE], Word *wp) {
  // Place the word's letters vertically across the board array
  for (int i = 0; i < wp->length; i++)
    board[wp->posr + i][wp->posc] = wp->word[i];
}

void display(FILE *fp, char board[][BOARD_SIZE]) {
  // Print out the board array with a border wall around it
  for (int x = 0; x < BOARD_SIZE + 2; x++) {
    if (x == 0 || x == BOARD_SIZE + 1) {
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
  // Initialize two empty boards
  char sol_board[BOARD_SIZE][BOARD_SIZE];
  init_board(sol_board);
  char empty_board[BOARD_SIZE][BOARD_SIZE];
  init_board(empty_board);

  // Fill the solution board with . and letters, and fill the empty board with # and spaces
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

  // Display both boards
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
    // Print the word positions, directions, and clues
    fprintf(fp, "%4d,%-4d| %9s | %s\n", clues[i].posr + 1, clues[i].posc + 1, dir, clues[i].anagram);
  }
}

int place_words(char board[][BOARD_SIZE], Word *wp, int count, Word placed_words[], int placed_count) {
  int amt_tried = 0;
  int amt_success = 0;
  // Check if first word
  if (wp->order == 0 && !wp->placed) {
    // Calculate starting positions
    wp->posr = (BOARD_SIZE / 2);
    wp->posc = (BOARD_SIZE / 2) - (wp->length / 2);
    wp->orientation = 'h';

    // Place the word
    hplace(board, wp);
    wp->placed = 1;

    // Add to record
    placed_words[amt_tried] = *wp;
    
    // Increment the word pointer and the amount tried/success
    wp++;
    amt_tried++;
    amt_success++;
  }
  // While the end of the words list has not been reached
  while (amt_tried < count) {
    // If the word has already been placed, ignore it
    if (wp->placed) {
      wp++;
      amt_tried++;
      continue;
    }
    // Get the intersecting letter
    Letter letter = get_intersection(board, wp, amt_tried, count);

    // If no intersecting letter exists, increment the word pointer and the amount tried and move onto the next word
    if (letter.letter == '!') {
      wp++;
      amt_tried++;
      continue;
    }
    
    int posr, posc;
    
    // See if the intersected word is vertical or horizontal
    // Set the positions of the word to be placed so that it intersects with the other word
    // Set the orientation to be opposite of the intersecting word
    // Place the word
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
    // The record shows the word is placed
    wp->placed = 1;

    // Add the placed word to the placed words list
    placed_words[amt_success + placed_count] = *wp;


    // Increment the word pointer, amount tried, and amount success
    wp++;
    amt_tried++;
    amt_success++;
  }

  // Return the amount of successful places
  return amt_success;
  
}

Letter get_intersection(char board[][BOARD_SIZE], Word *wp, int amt_tried, int total) {
  Letter letter;
  Word *current = wp;

  // Set the word pointer to the beginning of the word list
  for (int i = 0; i < amt_tried; i++) {
    wp--;
  }

  for (int i = 0; i < total; i++) {
    // If the word has been placed
    if (wp->placed == 1) {
      // See if there are any matching letters
      for (int j = 0; j < current->length; j++) {
	for (int k = 0; k < wp->length; k++) {

	  // If there is a matching letter	  
	  if (current->word[j] == wp->word[k]) {
	    // Set the letter to the letter and the positions of the letter in each word to the offsets
	    // Set the intersect word pointer to the intersecting word
	    letter.letter = current->word[j];
	    letter.offset_current = j;
	    letter.offset_intersect = k;
	    letter.intersect = wp;

	    // Check whether the word can be placed
	    if (check_pos(board, current, letter)) {
	      // If the word can be placed, return the letter
	      return letter;
	    }
	  }
	}
      }
    }
    // Increment the word pointer
    wp++;
  }

  // If no words can be cleanly intersected with, set the intersection letter to ! to signify so
  letter.letter = '!';
  
  return letter;
}

int check_pos(char board[][BOARD_SIZE], Word *current, Letter letter) {
  int startr, endr;
  int startc, endc;

  // Determine the bounds of rows and columns to check
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

  // If the starting or ending position of the word/checking area is outside the bounds of the board
  if (startc < -1 || endc > BOARD_SIZE || startr < -1 || endr > BOARD_SIZE) {
    // Return 0 to say this word CANNOT be placed
    return 0;
  }

  // Looping over the bounds of rows and columns
  for (int r = startr; r <= endr; r++) {
    for (int c = startc; c <= endc; c++) {
      // If the checking area starts outside or ends outside the board, ignore it
      // The word will still fit inside the board
      if (r < 0 || c < 0 || r >= BOARD_SIZE || c >= BOARD_SIZE) continue;

      // Ignore the intersection word's row/column
      if (letter.intersect->orientation == 'h' && r == letter.intersect->posr) continue;
      if (letter.intersect->orientation == 'v' && c == letter.intersect->posc) continue;

      // Check for blank spaces
      if (board[r][c] != ' ') {
	return 0;
      }
    }
  }
  return 1;
}

void generate_anagrams(Clue clues[], int count) {
  for (int i = 0; i < count; i++) {
    // For each word
    char word[BOARD_SIZE + 1];
    strcpy(word, clues[i].sol);

    // Scramble the word
    scramble(word);

    // Place the scrambled word in the clue's anagram
    strcpy(clues[i].anagram, word);
  }
}

void scramble(char word[]) {
  int len = strlen(word);
  char original[len];
  int count = 0;
  strcpy(original, word);
  // Scramble
  srand(time(NULL));

  while (!strcmp(original, word) && count < 5) {
    // For twice the length of the word
    for (int i = 0; i < len * 2; i++) {
      // Pick two random characters in the word
      int i1 = rand() % len;
      int i2 = rand() % len;

      // Swap the random characters
      char temp;
      temp = word[i1];
      word[i1] = word[i2];
      word[i2] = temp;

      // Backup counter to ensure words like "AAAAA" won't keep this in a loop
      count++;
    }
  }
}
