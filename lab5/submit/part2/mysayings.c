// Name: mysayings.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 5 Part 2
// Description: A Sayings Manager

#include <stdio.h>
#include <string.h>

// Macros
#define MAX_LENGTH 256
#define MAX_SAYINGS 50
#define MAX_FILENAME 30

// Function Prototypes
int collect_sayings(FILE *, char [][MAX_LENGTH]);
int display_menu();
void display_sayings(char [][MAX_LENGTH], int);
int enter_saying(char [][MAX_LENGTH], int);
void list_saying_contains(char [][MAX_LENGTH], int);
void save_sayings(char [][MAX_LENGTH], int);
void prune_newline(char []);

int main() {

  // Variables
  char filename[MAX_FILENAME];
  FILE *fp;
  char sayings[MAX_SAYINGS][MAX_LENGTH];
  int size, option, operating;


  // Open file
  printf("Enter the input sayings file: ");
  fgets(filename, MAX_FILENAME, stdin);
  prune_newline(filename);
  fp = fopen(filename, "r");
  // Check if the file exists
  if (!fp) {
    // If the file does not exist, give the user an error message
    printf("Error: file %s not found\n", filename);
    // End the program
    return 1;
  }

  // Read all the sayings from the file and count them
  size = collect_sayings(fp, sayings);

  // Run the main loop of the program
  operating = 1;
  while(operating) {

    // Print the option menu
    option = display_menu();

    switch(option) {
    case 1:
      // Display all the sayings
      display_sayings(sayings, size);
      break;
    case 2:
      // Allow the user to input a saying, updating the size
      size = enter_saying(sayings, size);
      break;
    case 3:
      // Display the sayings containing a substring the user enters
      list_saying_contains(sayings, size);
      break;
    case 4:
      // Save the sayings to a new file
      save_sayings(sayings, size);
      break;
    case 5:
      // Stop the main loop and print a goodbye message
      operating = 0;
      printf("Goodbye!!\n");
      break;
    }
  }
  
  return 0;
}

void prune_newline(char str[]) {
  // Replace any fgets string's ending newline with a null character
  str[strlen(str) - 1] = '\0';
}

int collect_sayings(FILE *fp, char sayings[][MAX_LENGTH]) {
  int count = 0;
  // Read in the saying, prune the newline, and add to the sayings array
  while (1) {
    fgets(sayings[count], MAX_LENGTH, fp);
    prune_newline(sayings[count]);
    // If the end of the file is reached, stop the loop
    if (feof(fp))
      break;
    // Increase the count
    count++;
  }
  // Return the count to be taken as the size of the sayings array
  return count;
}

int display_menu() {
  int opt;

  // Give some space
  printf("\n\n");

  // Print the options
  printf("1) Display all sayings currently in the database\n");
  printf("2) Enter a new saying into the database\n");
  printf("3) List sayings that contain a given substring entered by the user\n");
  printf("4) Save all sayings in a new text file\n");
  printf("5) Quit the program\n");
  printf("Option: ");
  scanf("%d", &opt);
  getchar();

  // If an invalid option is input, throw an error and give the user a new menu
  if (opt < 1 || opt > 5) {
    printf("Error: option does not exist\n");
    opt = display_menu();
  }

  return opt;
}

void display_sayings(char sayings[][MAX_LENGTH], int size) {
  // Print out all the sayings
  for (int i = 0; i < size; i++) {
    printf("%2d. %s\n", i+1, sayings[i]);
  }
}

int enter_saying(char sayings[][MAX_LENGTH], int size) {
  // Take in the saying from the user prompt
  printf("Enter the saying: ");
  fgets(sayings[size], MAX_LENGTH, stdin);
  // Prune the newline
  prune_newline(sayings[size]);
  // Add to and return the size of the sayings array
  size++;
  return size;
}

void list_saying_contains(char sayings[][MAX_LENGTH], int size) {
  char contains[MAX_SAYINGS][MAX_LENGTH];
  char search[MAX_LENGTH];
  int count = 0;
  // Take in the substring from the user prompt
  printf("What substring do you want to search for: ");
  fgets(search, MAX_LENGTH, stdin);
  // Prune the newline
  prune_newline(search);
  // See if any string in sayings contains the substring
  for (int i = 0; i < size; i++) {
    if (strstr(sayings[i], search)) {
      // Add it to the "contains" array
      strcpy(contains[count], sayings[i]);
      count++;
    }
  }
  printf("\n");
  // Display the sayings containing the substring
  display_sayings(contains, count);
}

void save_sayings(char sayings[][MAX_LENGTH], int size) {
  FILE *nfp;
  char new_filename[MAX_FILENAME];
  // Take in the new file name from the user prompt
  printf("File to save to: ");
  fgets(new_filename, MAX_FILENAME, stdin);
  // Prune the newline
  prune_newline(new_filename);
  // Open the file in write mode
  nfp = fopen(new_filename, "w");
  // Every saying is written to the file with a newline after
  for (int i = 0; i < size; i++) {
    fputs(sayings[i], nfp);
    fputs("\n", nfp);
  }
  // Success message printed
  printf("%d sayings saved to %s\n", size, new_filename);
}
