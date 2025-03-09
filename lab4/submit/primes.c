// Name: primes.c
// Author: Will Griffin
// Class: CSE 20311 - Fundamentals of Computing
// Assignment: Lab 4 Part 2
// Description: Prime Numbers

#include <stdio.h>

int main() {

  int primes[1000];
  int count = 1;

  for (int i = 0; i < 1000; i++)
    primes[i] = 1;

  for (int index = 2; index < 1000; index++) {
    if (primes[index]) {
      if (count % 10 != 0)
	printf("%4d", index);
      else {
	printf("%4d\n", index);
      }
      count++;
    }
    for (int j = index + 1; j < 1000; j++) {
      if (j % index == 0) {
	primes[j] = 0;
      }
    }
      
  }
  printf("\n");

  return 0;
  }
