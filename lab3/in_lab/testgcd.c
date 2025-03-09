#include <stdio.h>

int get_gcd(int, int);

int main() {
  int num1, num2;
  printf("Two numbers to find the GCD: ");
  scanf("%d %d", &num1, &num2);

  printf("The GCD is %d\n", get_gcd(num1, num2));

  return 0;
}

int get_gcd(int a, int b) {
  int smaller;
  int gcd;
  if (a > b)
    smaller = b;
  else
    smaller = a;

  for (int i = 1; i <= smaller; i++) {
    if (a % i == 0 && b % i == 0) {
      gcd = i;
    }
  }

  return gcd;
  
}
