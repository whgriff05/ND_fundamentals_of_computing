// Name: menucalc.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 3 Part 3
// Description: Text Menu Calculator

#include <stdio.h>


// Function prototypes
double add(double, double);
double subtract(double, double);
double multiply(double, double);
double divide(double, double);

int main() {

  // Variables
  int choice;
  double n1, n2;

  while (1) {
    // Prints the menu to the user and asks for their input
    printf("What would you like to do?\n");
    printf(" 1) Addition\n");
    printf(" 2) Subtraction\n");
    printf(" 3) Multiplication\n");
    printf(" 4) Division\n");
    printf(" 5) Quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // If the choice is not 1-5, tell the user to enter a valid option
    if (choice < 1 || choice > 5) {
      printf("Enter a valid option.\n");	
      printf("\n");
      continue;
    }

    // If the choice is exit, say goodbye and exit the loop
    if (choice == 5) {
      printf("Good bye.\n");
      printf("\n");
      break;
    }

    // Asks the user for two numbers
    printf("Enter two numbers: ");
    scanf("%lf %lf", &n1, &n2);

    // Depending on the operation choice, print to the user their inputs, operation, and output
    switch(choice) {
    case 1:
      printf("%g + %g = %g\n", n1, n2, add(n1, n2));
      break;
    case 2:
      printf("%g - %g = %g\n", n1, n2, subtract(n1, n2));
      break;
    case 3:
      printf("%g * %g = %g\n", n1, n2, multiply(n1, n2));
      break;
    case 4:
      // if division is selected and the second number is zero, print a divide by zero error
      if (n2 == 0) {
	printf("Error: attempted division by zero\n");
	break;
      }
      printf("%g / %g = %g\n", n1, n2, divide(n1, n2));
      break;
    }
    printf("\n");
    
  }
  return 0;
}

// Add two numbers
double add(double num1, double num2) {
  return num1 + num2;
}

// Subtract two numbers
double subtract(double num1, double num2) {
  return num1 - num2;
}

// Multiply two numbers
double multiply(double num1, double num2) {
  return num1 * num2;
}

// Divide two numbers
double divide(double num1, double num2) {
  return num1 / num2;
}
