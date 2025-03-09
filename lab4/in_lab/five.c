#include <stdio.h>

int main() {
  int nums[5];

  for (int i = 0; i < 5; i++) {
    printf("Enter a number: ");
    scanf("%d", &nums[i]);
  }

  for (int i = 4; i >= 0; i--) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  return 0;
}
