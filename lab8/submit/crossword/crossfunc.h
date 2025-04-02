#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global Variables
#define BOARD_SIZE 15
#define MAX_WORDS 20

// Structs
typedef struct {
  char word[BOARD_SIZE + 1];
  int length;
  int order;
  int posr;
  int posc;
  char orientation;
} Word;

typedef struct {
  char letter;
  int offset_current;
  int offset_intersect;
  Word *intersect;
} Letter;

typedef struct {
  char sol[BOARD_SIZE + 1];
  char anagram[BOARD_SIZE + 1];
  char orientation;
  int posr;
  int posc;
} Clue;

// Function Prototypes
void to_caps(char str[]);
void stringify(char str[]);
int get_words(FILE *fp, Word words[]);
int is_str_alpha(char str[]);
void sort(Word words[], int count);
void init_board(char board[][BOARD_SIZE]);
void hplace(char board[][BOARD_SIZE], Word *wp);
void vplace(char board[][BOARD_SIZE], Word *wp);
void display(FILE *fp, char board[][BOARD_SIZE]);
void display_boards(FILE *fp, char board[][BOARD_SIZE]);
void display_clues(FILE *fp, Clue clues[], int placed_word_count);
int place_words(char board[][BOARD_SIZE], Word *wp, int count, Word placed_words[]);
Letter get_intersection(char board[][BOARD_SIZE], Word *wp, int amt_tried);
int check_pos(char board[][BOARD_SIZE], Word *wp, Letter letter);
void generate_anagrams(Clue clues[], int count);
void scramble(char word[]);
