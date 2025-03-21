#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main() {
  char cur; // Символ
  int position = 1; // Номер слова в предлоежнии

  while (scanf("%c", &cur) != EOF) {
    if (cur != '\n') {
      if (cur != ' ') {
        if (isalpha(cur)) {
          int key = position;
          char offset = isupper(cur) ? 'A' : 'a';
          cur = (cur - offset - key + 26) % 26 + offset;
          printf("%c", cur);
        } else {
          printf("%c", cur);
        }
      } else {
        position++;
        printf("%c",' ');
      }
    } else {
      position = 1;
    }
  }
  return 0;
}
