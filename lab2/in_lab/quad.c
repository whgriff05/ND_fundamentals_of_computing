// quad.c
// computes the roots of a quadratic equation
#include <stdio.h>
#include <math.h>

int main()
{
  double a, b, c, disc;
  double x1, x2;

  printf("Enter the coefficients (a,b,c) of a quadratic equation: ");
  scanf("%lf %lf %lf", &a, &b, &c);
  printf("\n");

  disc = pow(b, 2) - (4 * a * c);

  if (disc == 0) {
    x1 = (-1 * b) / (2 * a);
    printf("Quadratic equation has one root: %lf\n", x1);
  } else if (disc > 0) {
    x1 = (-1 * b + sqrt(disc)) / (2 * a);
    x2 = (-1 * b - sqrt(disc)) / (2 * a);
    printf("Quadratic equation roots are: %lf and %lf\n", x1, x2);
  } else {
    printf("Quadratic equation has no real solutions.\n");
  }


  return 0;
}

