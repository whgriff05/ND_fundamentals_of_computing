#include <math.h>
#include <stdio.h>

int main() {

  int num;
  int sum_squares = 0;
  double sum_roots = 0;

  printf("Insert a number: ");
  scanf("%d", &num);

  for (int i = 0; i <= num; i++) {
    sum_squares += pow(i, 2);
    sum_roots += sqrt(i);
  }


  printf("Sum of squares of 1 through %d: %d\n", num, sum_squares);
  printf("Sum of roots of 1 through %d: %lf\n", num, sum_roots);
  
  return 0;
}
