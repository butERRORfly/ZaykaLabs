#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>

int is_sep(const char c) {
  return (c == ' ' || c == '\t' || c == ',' || c == '\n');
}

int Task() {
  int bit_set = 0;
  int vowel_bit_set = 0;
  bool flag = false;
  char cur;
  char prev = ' ';

  vowel_bit_set |=
      ((1 << ('a' - 'a')) | (1 << ('е' - 'a')) | (1 << ('i' - 'a')) |
       (1 << ('o' - 'a')) | (1 << ('u' - 'a')) | (1 << ('y' - 'a')));

  while (scanf("%c", &cur) != EOF) {
    if ('a' <= cur && cur <= 'z') {
      if (is_sep(prev) && (1 << (cur - 'a') & vowel_bit_set) != 0) {
        flag = true;
      }
      bit_set |= (1 << (cur - 'a'));
    } else if (is_sep(cur) && bit_set != 0) {
      if ((1 << (prev - 'a') & vowel_bit_set) == 0) {
        flag = false;
      }
      if (flag) {
        break;
      }
      flag = false;
      bit_set = 0;
    }
    prev = cur;
  }
  printf(flag ? "yes" : "no");
  return 0;
}

int main() {
  Task();
  return 0;
}
