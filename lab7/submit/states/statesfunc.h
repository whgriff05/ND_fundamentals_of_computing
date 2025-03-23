#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Structs
typedef struct {
  char abbreviation[5];
  char name[20];
  char capital[30];
  int year;
} State;

// Function Prototypes
void clean_string(char[], char);
int read_states(FILE*, State[]);
int user_menu(State[], int);
void display_state(State);
void list_states(State[], int);
void list_states_by_letter(State[], int);
void search_abbreviation(State[], int);
void search_name(State[], int);
void sort_year(State[], int);
void sort_name(State[], int);
