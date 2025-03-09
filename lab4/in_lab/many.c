#include <stdio.h>

int main()
{
  int a[20];      // the array of numbers (assume max of 20)
  int num;        // each number being read in
  int count = 0;  // number of elements read in

  printf("Enter a few positive integers, followed by a -1: ");

  do {
    printf("Number: ");
    scanf("%d", &num);
    if (num == -1) {
      break;
    }
    a[count] = num;
    count++;
  } while (num != -1);
  count--;


  for (int i = count; i >= 0; i--) {
    printf("%d ", a[i]);
  }
  printf("\n");
  
  return 0;
}

