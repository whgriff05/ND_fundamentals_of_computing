// teststates2.c
#include <stdio.h>
#include <string.h>

#define SIZE 50
#define LENGTH 20

void display1(char [][LENGTH], int);
void display2(char [][LENGTH], int);

int main()
{
  char states[SIZE][LENGTH];
  FILE *fp = fopen("states.txt", "r");
  char astate[LENGTH];

  int count = 0;
  while(1) {
    fgets(astate, LENGTH, fp);
    if (feof(fp)) break;
    astate[strlen(astate)-1] = '\0';
    strcpy(states[count], astate);
    count++;
  }
  
  display1(states, count);
  display2(states, count);

  return 0;
}

void display1(char states[][LENGTH], int count)
{
  for (int i = 0; i < count; i++)
    printf("%s\n", states[i]);
}

void display2(char states[][LENGTH], int count)
{
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < strlen(states[i]); j++)
      printf("%c ", states[i][j]);
    printf("\n");
  }
}

