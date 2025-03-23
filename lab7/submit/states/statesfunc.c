#include "statesfunc.h"

// Global sort variable
int sorted_by_year = 0;

// Function to either make the whole string uppercase or lowercase
void clean_string(char str[], char lettercase) {
  // Loops through all the letters
  for (int i = 0; i < strlen(str); i++) {
    if (lettercase == 'l') {
      // Makes all letters lowercase
      if (str[i] >= 'A' && str[i] <= 'Z') {
	str[i] = tolower(str[i]);
      }
    } else if (lettercase == 'u') {
      // Makes all letters uppercase
      if (str[i] >= 'a' && str[i] <= 'z') {
	str[i] = toupper(str[i]);
      }
    }
  }
}

int read_states(FILE *fp, State states[]) {
  int count = 0;

  while (1) {
    // Gets a line from the file
    char line[100];
    fgets(line, 100, fp);

    // If the end of the file is reached, break the program
    if (feof(fp)) break;

    // Input the respective information separated by commas into a state struct in the states array
    strcpy(states[count].abbreviation, strtok(line, ","));
    strcpy(states[count].name, strtok(NULL, ","));
    strcpy(states[count].capital, strtok(NULL, ","));
    states[count].year = atoi(strtok(NULL, "\n"));

    // Increment the count
    count++;
  }

  // Return the final count of the states
  return count;
}

int user_menu(State states[], int count) {
  int choice;

  // Print the user menu
  printf("\n\n");
  printf("1) List all states\n");
  printf("2) List states by letter\n");
  printf("3) Search state by abbreviation\n");
  printf("4) Search state by name\n");
  // Depending on how the list is sorted, display the corresponding opposite option
  if (sorted_by_year) {
    printf("5) Sort states by name\n");
  } else {
    printf("5) Sort states by year admitted to the union\n");
  }
  printf("6) Quit\n");

  // Get the user's choice
  printf(" > ");
  scanf("%d", &choice);

  switch(choice) {
  case 1:
    list_states(states, count);
    break;
  case 2:
    list_states_by_letter(states, count);
    break;
  case 3:
    search_abbreviation(states, count);
    break;
  case 4:
    search_name(states, count);
    break;
  case 5:
    // Depending on how the list is sorted, call the corresponding opposite sort function
    if (sorted_by_year) {
      sort_name(states, count);
    } else {
      sort_year(states, count); 
    }
    break;
  case 6:
    // The function returns -1, telling the main driver to exit the program
    return -1;
    break;
  default:
    // Give the user instructions on what to enter and reprint the menu and get an option
    printf("Error: invalid choice given (choice should be between 1-5)\n\n");
    return user_menu(states, count);
    break;
  }

  return 0;
}

void display_state(State s) {
  // Print the state's data
  printf("%s (%s) | Capital: %s | Joining Year: %d\n", s.name, s.abbreviation, s.capital, s.year);
}

void list_states(State s[], int count) {
  // Display all states' data
  for (int i = 0; i < count; i++) {
    display_state(s[i]);
  }
}

void list_states_by_letter(State s[], int count) {
  char letter;
  int amt = 0;

  // Get a letter from the user
  printf("\n");
  printf("Letter: ");
  scanf(" %c", &letter);

  // Make it uppercase so it can be used to search for states beginning with the letter
  letter = toupper(letter);

  for (int i = 0; i < count; i++) {
    // If the state starts with that letter, display the state's data
    if (letter == s[i].name[0]) { display_state(s[i]); amt++; }
  }
  if (amt == 0) {
    // If no states start with that letter, print a message explaining so
    printf("There are no states starting with the letter %c\n", letter);
  }
  
}

void search_abbreviation(State s[], int count) {
  char abbrev[5];

  // Get an abbreviation from the user
  printf("\n");
  printf("Abbreviation: ");
  scanf(" %s", abbrev);

  // Make the entire abbreviation uppercase
  clean_string(abbrev, 'u');

  printf("\n");

  for (int i = 0; i < count; i++) {
    // Search for the state with the matching abbreviation
    if (!strcmp(abbrev, s[i].abbreviation)) {
      // Display the state's data and stop the loop
      display_state(s[i]);
      return;
    }
  }
  // If no states are found, print to the user
  printf("There are no states with the abbreviation %s\n", abbrev);
}

void search_name(State s[], int count) {
  char n[20];

  // Get a name from the user
  printf("\n");
  printf("Name: ");
  scanf(" %s", n);

  // Make the entire string lowercase
  clean_string(n, 'l');
  // Make the first letter uppercase
  n[0] = toupper(n[0]);

  printf("\n");

  for (int i = 0; i < count; i++) {
    // Search for the state with the matching name
    if (!strcmp(n, s[i].name)) {
      // Display the state's data and stop the loop
      display_state(s[i]);
      return;
    }
  }
  // If no states are found, print to the user
  printf("There are no states with the name %s\n", n);
}

void sort_year(State s[], int count) {
  // Uses the bubble sort algorithm to sort the states by their years admitted to the union
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      // Compares simultaneous pairs of states' years
      if (s[j].year > s[j+1].year) {
	// If the one ahead is earlier, swap the two
	State temp = s[j];
	s[j] = s[j+1];
	s[j+1] = temp;
      }
    }
  }

  // Set the global variable so the program knows how the data is sorted
  sorted_by_year = 1;
}

void sort_name(State s[], int count) {
  // Uses the bubble sort algorithm to sort the states by their names
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      // Compares simultaneous pairs of states' names
      if (strcmp(s[j].name, s[j+1].name) > 0) {
	// strcmp returns 1 if the strings have a difference and the first string's char value is greater than the second string's char in the same place
	// If the one ahead has an earlier char value, swap the two (sort alphabetically)
	State temp = s[j];
	s[j] = s[j+1];
	s[j+1] = temp;
      }
    }
  }
  
  // Set the global variable so the program knows how the data is sorted
  sorted_by_year = 0;
}


