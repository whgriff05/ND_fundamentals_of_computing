// addup.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int n1, n2, sum;

   if (argc == 1) {  // A
     printf("enter two integers: ");
     scanf("%d %d", &n1, &n2);
   } else if (argc == 2) {  // B
     printf("incorrect usage: too few arguments\n");
     return 1;
   } else if (argc == 3) {  // C
     n1 = atoi(argv[1]);  // D
     n2 = atoi(argv[2]);  // E
   } else {
      printf("incorrect usage: too many arguments\n");
      return 2;
   }

   sum = n1 + n2;
   printf("the sum is: %d\n", sum);
  
   return 0;
}

