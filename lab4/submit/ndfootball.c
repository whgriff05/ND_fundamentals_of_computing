// Name: ndfootball.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 4 Part 3
// Description: ND Football

#include <stdio.h>
#include "nd_data.h"


// Global Variables
const int starting_year = 1900;
const int size = sizeof(wins) / sizeof(wins[0]);
const int max_year = starting_year + size - 1;

// Function Prototypes
int display_menu();
void display_record();
void display_n_losses();
void display_n_wins();
void display_avg_wins();
void display_avg_losses();

int main() {
  int ended = 0;

  while (!ended) {
    // Display the selection menu
    int option = display_menu();    

    switch(option) {
    case 1:
      display_record();
      break;
    case 2:
      display_n_losses();
      break;
    case 3:
      display_n_wins();
      break;
    case 4:
      display_avg_wins();
      break;
    case 5:
      display_avg_losses();
      break;
    case 6:
      // End the menu loop and display a goodbye message
      ended = 1;
      printf("Good bye!\n");
      break;
    default:
      printf("Invalid choice. Please try again.");
      break;
    }
    printf("\n\n");

  }


  return 0;
}

int display_menu() {
  int opt;
  
  // Print the menu
  printf("ND Football Stats\n");
  printf("1: Display the record for a year\n");
  printf("2: Display years with at least \"n\" losses\n");
  printf("3: Display years with at least \"n\" wins\n");
  printf("4: Display average wins between two years\n");
  printf("5: Display average losses between two years\n");
  printf("6: Exit\n");

  // Get the user input
  printf("Option: ");
  scanf("%d", &opt);

  return opt;
}

void display_record() {
  int year;

  // Get the user input for which year
  printf("Year: ");
  scanf("%d", &year);

  // Make sure year is within data bounds
  if (year < starting_year || year > max_year) {
    printf("Invalid year entered.");
    return;
  }

  // Find the wins and losses for the input year
  int record_wins = wins[year - starting_year];
  int record_losses = losses[year - starting_year];

  // Display the record to the user
  printf("Record: %d - %d\n", record_wins, record_losses);
}

void display_n_losses() {
  int input_losses;

  // Get the user input
  printf("Losses: ");
  scanf("%d", &input_losses);

  // Check for reasonable data (team cannot have less than 0 losses)
  if (input_losses < 0) {
    printf("Invalid losses entered.");
    return;
  }

  // Print all years with at least the input amount of losses
  printf("Years with at least %d losses: ", input_losses);
  for (int i = 0; i < size; i++) {
    if (input_losses <= losses[i])
      printf("%d ", i + starting_year);
  }
}

void display_n_wins() {
  int input_wins;

  // Get the user input
  printf("Wins: ");
  scanf("%d", &input_wins);

  // Check for reasonable data (team cannot have less than 0 wins)
  if (input_wins < 0) {
    printf("Invalid wins entered.");
    return;
  }

  // Print all years with at least the input amount of wins
  printf("Years with at least %d wins: ", input_wins);
  for (int i = 0; i < size; i++) {
    if (input_wins <= wins[i])
      printf("%d ", i + starting_year);
  }
}

void display_avg_wins() {
  int initial_year;
  int final_year;

  // Get the user input for initial year
  printf("Initial Year: ");
  scanf("%d", &initial_year);

  // Check if the year is within data bounds
  if (initial_year < starting_year || initial_year > max_year) {
    printf("Invalid year entered.");
    return;
  }

  // Get the user input for final year
  printf("Final Year: ");
  scanf("%d", &final_year);

  // Check if the year is within data bounds
  if (final_year < starting_year || final_year > max_year) {
    printf("Invalid year entered.");
    return;
  }

  // Check if the years are in chronological order
  if (final_year <= initial_year) {
    printf("Invalid range of years entered.");
    return;
  }

  float sum_wins = 0;

  // Add up all the wins between the initial and final year
  for (int i = (initial_year - starting_year); i < (final_year - starting_year); i++ ) {
    sum_wins += wins[i];
  }

  // Calculate and display the average
  float avg = sum_wins / (final_year - initial_year);
  printf("Average wins between %d and %d: %0.2f wins per year", initial_year, final_year, avg);
}

void display_avg_losses() {
  int initial_year;
  int final_year;

  // Get the user input for initial year
  printf("Initial Year: ");
  scanf("%d", &initial_year);

  // Check if the year is within data bounds
  if (initial_year < starting_year || initial_year > max_year) {
    printf("Invalid year entered.");
    return;
  }

  // Get the user input for final year
  printf("Final Year: ");
  scanf("%d", &final_year);

  // Check if the year is within data bounds
  if (final_year < starting_year || final_year > max_year) {
    printf("Invalid year entered.");
    return;
  }
  
  // Find the wins and losses for the input year
  if (final_year <= initial_year) {
    printf("Invalid range of years entered.");
    return;
  }

  float sum_losses = 0;
  
  // Add up all the wins between the initial and final year
  for (int i = (initial_year - starting_year); i < (final_year - starting_year); i++ ) {
    sum_losses += losses[i];
  }

  // Calculate and display the average
  float avg = sum_losses / (final_year - initial_year);
  printf("Average losses between %d and %d: %0.2f losses per year", initial_year, final_year, avg);
}
