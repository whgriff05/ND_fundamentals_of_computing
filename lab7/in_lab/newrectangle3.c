// newrectangle3.c
#include <stdio.h>

typedef struct {
  float length;
  float width;
  float area;
  float perimeter;
} Rectangle; 

int readvalues(FILE *, Rectangle []);

float find_area(Rectangle);
float find_perim(Rectangle);
void display(Rectangle);

int main()
{
  FILE *fp = fopen("values.txt", "r");
  Rectangle rect_arr[10]; 
   
  // read the length and width values, and
  // count the number of rectangles in the process
  // ...
  int rect_count = readvalues(fp, rect_arr);

  // update the rectangles by computing the areas and perimeters
  // ...
  for (int i = 0; i < rect_count; i++) {
    rect_arr[i].perimeter = find_perim(rect_arr[i]);
    rect_arr[i].area = find_area(rect_arr[i]);
  }

  // display the info
  // ...
  for (int i = 0; i < rect_count; i++) {
    display(rect_arr[i]);
  }

  return 0; 
}

int readvalues(FILE *fp, Rectangle arr[])
{ 
  // ...
  int rect_count = 0;
  while (1) {

    fscanf(fp, "%f", &arr[rect_count].length);
    fscanf(fp, "%f", &arr[rect_count].width);

    if (feof(fp)) break;
    
    rect_count++;
  }
  return rect_count;

}

float find_area(Rectangle r)
{
  return r.length*r.width;
}

float find_perim(Rectangle r)
{
  return 2*(r.length + r.width);
}

void display(Rectangle r)
{
  printf("rectangle is %g x %g\n", r.length, r.width);
  printf("  its area is %g\n", r.area);
  printf("  its perimeter is %g\n", r.perimeter);
}

