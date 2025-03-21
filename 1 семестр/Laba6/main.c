#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void decode_caesar(char *text) {
    char *word;
    int word_position = 0;
    // Сепаратор
    char *sep = " \n";
    word = strtok(text, sep);
    while (word != NULL) {
        word_position++;
        int key = word_position; // Ключ равен номеру слова
        // Раскодирование каждого символа в слове
        for (int i = 0; i < strlen(word); i++) {
            if (isalpha(word[i])) {
                char offset = isupper(word[i]) ? 'A' : 'a';
                word[i] = (word[i] - offset - key + 26) % 26 + offset; // Логический сдвиг
            }
        }
        printf("%s ", word); // Вывод раскодированного слова
        word = strtok(NULL, sep); // Переход к следующему слову
    }
}


int main() {
    FILE *file;
    char *filename = "in.txt";
    char text[256];

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return EXIT_FAILURE;
    }

    while (fgets(text, sizeof(text), file)) {
        printf("Закодированный текст: %s", text);
        printf("\nРаскодированный текст: ");
        decode_caesar(text);
        printf("\n");
    }

    fclose(file);
    return EXIT_SUCCESS;
}