// fib2.c
#include <stdio.h>
#include <time.h>

int fib_loop(int);
int fib_rec(int);

int main()
{
  int n;
  clock_t start, end;

  printf("Enter a number: ");
  scanf("%d", &n);

  printf("\nLoop:\n");
  start = clock();
  printf("  fibonacci of %d is %d\n", n, fib_loop(n));
  end = clock();
  printf("  time: %f\n", (float) (end-start) / CLOCKS_PER_SEC);

  printf("\nRecursion:\n");
  start = clock();
  printf("  fibonacci of %d is %d\n", n, fib_rec(n));
  end = clock();
  printf("  time: %f\n", (float) (end-start) / CLOCKS_PER_SEC);


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

