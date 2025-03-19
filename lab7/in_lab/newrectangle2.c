// newrectangle2.c
#include <stdio.h>

typedef struct {
  float length;
  float width;
  float area;
  float perimeter;
} Rectangle; 

float find_area(Rectangle);
float find_perim(Rectangle);
void display(Rectangle);

int main()
{
  Rectangle r1 = {5.5, 7.7}, r2 = {9.2, 6.4};

  r1.area = find_area(r1); 
  r1.perimeter = find_perim(r1); 

  r2.area = find_area(r2); 
  r2.perimeter = find_perim(r2); 

  display(r1);
  display(r2);

  return 0; 
}

float find_area(Rectangle r)
{
  return r.length*r.width ;
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

