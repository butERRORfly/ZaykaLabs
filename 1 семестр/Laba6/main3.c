#include <stdio.h>

int Mod(int x, int y) {
  if (y != 0) {
    return x % y;
  } else {
    return 0;
  }
}


int main() {
  int i = -11;
  int j = -6;
  int l = -5;

  for (int k=0; k<=50; ++k) {
    i = Mod((i + j + l) * (k + 1), 25) - Mod((i * j * k * (k + 2)), 10) + 10;
    printf("%d\n", i);
  }
}
