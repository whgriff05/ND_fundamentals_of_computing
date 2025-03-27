#include <ctype.h>
#include <stdio.h>
#include <string.h>

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

// Function Prototypes
int get_words(FILE *fp, Word words[]);
int is_str_alpha(char str[]);
void sort(Word words[], int count);
void init_board(char board[][BOARD_SIZE]);
void hplace(char board[][BOARD_SIZE], Word *wp);
void vplace(char board[][BOARD_SIZE], Word *wp);
void display(char board[][BOARD_SIZE]);
void display_boards(char board[][BOARD_SIZE]);
void place_words(char board[][BOARD_SIZE], Word *wp, int count);
Letter get_intersection(char board[][BOARD_SIZE], Word *wp, int amt_tried);
int check_pos(char board[][BOARD_SIZE], Word *wp, Letter letter);
