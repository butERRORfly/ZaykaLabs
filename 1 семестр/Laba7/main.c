#include <stdio.h>

// Есть ли слова , начинающиеся и закапчивающиеся гласными (согласными)?

int vowels_set = ((1 << ('a' - 'a')) | (1 << ('e' - 'a')) | (1 << ('u' - 'a')) |
                  (1 << ('i' - 'a')) | (1 << ('o' - 'a')) |
                  (1 << ('y' - 'a'))); // гласные буквы

// если символ является разделителем
int is_char_sep(const char l) {
  if (l == ' ' || l == '\n' || l == '\t' || l == EOF) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  int letters_set = 0;       // наш алфавит
  char prev_letter = ' ';    // предыдущая буква
  int flag1 = 0;             // первая буква гласная или нет
  int flag2 = 0;             // последняя буква гласная или нет
  int vowels_counter = 0;    // счетчик подходящих слов гласные
  int consonant_counter = 0; // счетчик подходящих слова согласные
  char l;                    // текущая буква

  while (scanf("%c", &l) != EOF) {
    if (is_char_sep(prev_letter) == 1) {
      if (((1 << (l - 'a')) & vowels_set) != 0) {
        flag1 = 1; // первая буква гласная
      } else {
        flag1 = 0;
      }
      letters_set = (letters_set | (1 << (l - 'a'))); // добавляем букву в set
    } else if (is_char_sep(l) == 1 && letters_set != 0) {
      if (((1 << (prev_letter - 'a')) & vowels_set) != 0) {
        flag2 = 1;
        if ((flag1 == 1) && (flag2 == 1)) {
          ++vowels_counter;
        }
      } else {
        flag2 = 0;
        if ((flag1 == 0) && (flag2 == 0)) {
          ++consonant_counter;
        }
      }
      letters_set = 0;
      flag1 = 0;
      flag2 = 0;
    }
    prev_letter = l;
  }
  if (consonant_counter == 0 && vowels_counter == 0) {
    printf("\n%s\n",
           "Все слова начинаются и заканчиваются согласной-гласной или "
           "гласной-согласной");
  } else {
    printf("\nКол-во слов, заканчивающихся и начинающихся согласными: %d\n",
           consonant_counter);
    printf("Кол-во слов, заканчивающихся и начинающихся гласными: %d\n",
           vowels_counter);
  }
}
