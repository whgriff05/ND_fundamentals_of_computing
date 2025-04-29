// fib1.c
#include <stdio.h>
#include <time.h>

int fib_loop(int);
int fib_rec(int);

int main()
{
  int n;

  printf("Enter a number: ");
  scanf("%d", &n);

  printf("\nLoop:\n");
  printf("  fibonacci of %d is %d\n", n, fib_loop(n));

  printf("\nRecursion:\n");
  printf("  fibonacci of %d is %d\n", n, fib_rec(n));

  return 0;
}

int fib_loop(int n)
{
  int fm2 = 0, fm1 = 1;
  int fibon;

  if (n == 0 || n == 1) 
    fibon = n;
  else {
    for(int i = 2; i <= n; i++) {
      fibon = fm2 + fm1;
      fm2 = fm1;
      fm1 = fibon;
    } 
  }

  return fibon;
}

int fib_rec(int n)
{
  if (n == 0 || n == 1)
    return n;
  else
    return fib_rec(n-1) + fib_rec(n-2);
}

//  OR:
//   return (n == 0 || n == 1) ? n : fib_rec(n-1) + fib_rec(n-2);

