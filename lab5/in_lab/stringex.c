// stringex.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convert(char []);

int main()
{
  char line[80];

  printf("enter a line: ");
  fgets(line, 80, stdin);
  line[strlen(line)-1] = '\0';

  convert(line);

  printf("%s\n", line);

  return 0;
}

void convert(char str[])
{
  int current = 0;
  while (str[current] != '\0') {
    if (isspace(str[current]))
      str[current] = '_';
    else
      str[current] = tolower(str[current]);
    current++;
  }


}

