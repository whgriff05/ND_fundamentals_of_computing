// Name: letterfreq.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 5 Part 1
// Description: Justifying Scrabble's Letter Point Values

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function Prototypes
int count_char(int[], char);
int total_letters(int[], int);
void display_stats(char[], int[], int, int);

int main() {
  // Variables
  const int alphabet_count = 26;

  int letters[alphabet_count];
  char current_char;
  int extra_chars = 0;
  
  FILE *fp;
  char filename[20];

  // Pre-fill the letters array with 0s
  for (int i = 0; i < alphabet_count; i++) {
    letters[i] = 0;
  }

  // Ask the user for the input file name
  printf("Enter the input file: ");
  fgets(filename, 20, stdin);
  // Add the null character to mark the end of the string
  filename[strlen(filename)-1] = '\0';

  // Try to open the file
  fp = fopen(filename, "r");
  if (!fp) {
    // If the file does not exist, give the user an error message
    printf("Error: file %s not found\n", filename);
    // End the program
    return 1;
  }

  // Process characters while the end of file has not been reached
  while (1) {
    current_char = fgetc(fp);
    if (feof(fp))
      break;
    extra_chars += count_char(letters, current_char);
  }

  // Display the final calculated letter counts and percentage stats
  display_stats(filename, letters, alphabet_count, extra_chars);
  
  return 0;
}

int count_char(int count[], char current) {
  // Set the character to its lowercase variant
  current = tolower(current);
  if (!isalpha(current))
    // If the character isn't a letter, return a 1 to add to the "non-letter" character count
    return 1;
  else
    // Add 1 to that letter's array index
    count[current - 97]++;
  return 0;
}

int total_letters(int letters[], int count) {
  // Loop through all letter indexes in the array
  int total = 0;
  for (int i = 0; i < count; i++) {
    // Add the count of that letter to the total
    total += letters[i];
  }
  // Return the total
  return total;
}

void display_stats(char file[], int letters[], int count, int extra) {
  // Calculate the total letters and total characters in the file
  int total_lett = total_letters(letters, count);
  int total_chars = total_lett + extra;

  // Print the total statistics
  printf("General summary for %s:\n", file);
  printf("  There were %d total characters\n", total_chars);
  printf("  There were %d letters\n", total_lett);

  printf("\n");
  printf("Letter counts:\n");

  for (int i = 0; i < count; i++) {
    // Print the letter and its count
    printf("%c:%8d  ", i+97, letters[i]);
    // Formatting so every 6 letters it prints a newline
    if ((i+1) % 6 == 0 && i != 0)
      printf("\n");
  }

  printf("\n\n");
  printf("Letter percentages:\n");
  for (int i = 0; i < count; i++) {
    // Print the letter and its percentage of appearance in the file
    printf("%c: %4.1f%%    ", i+97, ((float)letters[i] / total_lett) * 100);
    // Formatting so every 6 letters it prints a newline
    if ((i+1) % 6 == 0 && i != 0)
      printf("\n");
  }
  printf("\n");
}
