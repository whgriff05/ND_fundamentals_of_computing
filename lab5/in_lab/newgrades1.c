// newgrades1.c
//  reading data from a file (file's name is hard-coded)
#include <stdio.h>

float find_avg(int [], int);

int main()
{
  int grades[50], grd;
  int count = 0;
  FILE *fp;

  fp = fopen("thegrades.dat", "r");  // note: file name is hard-coded here

  while (1) {
    fscanf(fp, "%d", &grd);   // read the next grade
    if(feof(fp)) break;       // end the loop if EOF reached
    grades[count] = grd;      // put the grade in the array
    count++;                  // increment the count
  }

  float avg = find_avg(grades, count);
  printf("there are %d grades\n", count);
  printf("their average is: %.2lf\n", avg);

  return 0;
}

float find_avg(int g[], int sz)
{
  int g_sum = 0;

  for (int i = 0; i < sz; ++i) 
    g_sum = g_sum + g[i];

  return (float) g_sum / sz;
}

