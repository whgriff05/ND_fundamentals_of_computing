// Name: mortgage.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 2 Part 2
// Description: Mortgage Calculator
#include <stdio.h>

int main() {

  // Variables
  double principle;
  double rate;
  double monthly_payment;
  double total = 0;
  int months = 0;

  // Ask user for initial values
  printf("What is the principle (initial payment): $");
  scanf("%lf", &principle);
  printf("What is the rate (as a percent without the %% sign): ");
  scanf("%lf", &rate);
  // Convert given percentage to decimal value (5% -> 0.05)
  rate = rate / 100;
  printf("What is the payment each month: $");
  scanf("%lf", &monthly_payment);

  // Check for inputs being a negative number (not allowed)
  if (principle <= 0 || rate <= 0 || monthly_payment <= 0) {
    printf("One of the inputs was a negative number, resulting in an incorrect mortgate.\n");
    return 1;
  }
  
  // Check for interest being greater than the monthly payment
  if ((principle * (rate / 12)) > monthly_payment) {
    printf("Error: You're paying too little, the mortgage cannot be payed off at this amount per month.");
    return 1;
  }

  // Print table header
  printf("Month     Payment     Interest     Balance\n");

  // Loop for every month of payment
  while (principle > 0) {
    // Calculate the interest added to the principle
    double interest = principle * (rate / 12);
    principle += interest;

    // See if the full monthly payment will be made
    if (principle > monthly_payment) {
      principle -= monthly_payment;
      printf("%-5d     $%-.2lf    $%-6.2lf      $%-.2lf\n", months, monthly_payment, interest, principle);
    } else {
      monthly_payment = principle;
      printf("%-5d     $%-.2lf    $%-6.2lf      $%-.2lf\n", months, monthly_payment, interest, principle);
      principle -= monthly_payment;
    }
    
    // Keep track of the overall amount paid    
    total += monthly_payment;
    months++;
  }

  // Final total message with mortgage time covered
  printf("You paid a total of $%.2lf over %d years and %d months.\n", total, months / 12, months % 12);


  return 0;
}
