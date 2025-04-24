#include "kernel.h"

// Реализация my_strlen
size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Реализация my_strdup
char* my_strdup(const char* str) {
    size_t len = my_strlen(str) + 1;
    char* new_str = malloc(len);
    if (new_str == NULL) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        new_str[i] = str[i];
    }
    return new_str;
}

// Реализация my_strcmp
int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Инициализация таблицы
void initTable(SongTable* table) {
    table->size = 0;
    table->capacity = 10;
    table->entries = malloc(table->capacity * sizeof(TableEntry));
}

// Увеличение емкости таблицы
void increaseCapacity(SongTable* table) {
    table->capacity *= 2;
    table->entries = realloc(table->entries, table->capacity * sizeof(TableEntry));
}

// Добавление записи в таблицу
void addEntry(SongTable* table, long key, const char* value) {
    if (table->size == table->capacity) {
        increaseCapacity(table);
    }
    
    table->entries[table->size].key = key;
    table->entries[table->size].value = my_strdup(value);
    table->size++;
}

// Освобождение памяти таблицы
void freeTable(SongTable* table) {
    for (int i = 0; i < table->size; i++) {
        free(table->entries[i].value);
    }
    free(table->entries);
    table->size = 0;
    table->capacity = 0;
}

// Печать таблицы
void printTable(const SongTable* table) {
    printf("№\tКлюч\t\tЗначение\n");
    printf("--------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        printf("%d\t%ld\t\t%s\n", i+1, table->entries[i].key, table->entries[i].value);
    }
    printf("\n");
}

// Обмен двух записей таблицы
void swapEntries(TableEntry* a, TableEntry* b) {
    TableEntry temp = *a;
    *a = *b;
    *b = temp;
}

// Сортировка шейкером
void shakerSort(SongTable* table) {
    bool swapped = true;
    int start = 0;
    int end = table->size - 1;

    while (swapped) {
        swapped = false;

        // Проход слева направо
        for (int i = start; i < end; ++i) {
            if (table->entries[i].key > table->entries[i + 1].key) {
                swapEntries(&table->entries[i], &table->entries[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (table->entries[i].key > table->entries[i + 1].key) {
                swapEntries(&table->entries[i], &table->entries[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

// Двоичный поиск по ключу
int binarySearch(const SongTable* table, long key) {
    int left = 0, right = table->size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (table->entries[mid].key == key) {
            return mid;
        }
        
        if (table->entries[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Чтение слов из файла
int readWordsFromFile(const char* filename, char*** words) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int wordCount = 0;
    int capacity = 100;
    *words = malloc(capacity * sizeof(char*));
    
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%99s", word) == 1) {
        // Удаляем знаки препинания из слова
        int len = my_strlen(word);
        while (len > 0 && !isalpha(word[len - 1])) {
            word[len - 1] = '\0';
            len--;
        }
        
        if (len > 0) {
            if (wordCount == capacity) {
                capacity *= 2;
                *words = realloc(*words, capacity * sizeof(char*));
            }
            (*words)[wordCount] = my_strdup(word);
            wordCount++;
        }
    }
    
    fclose(file);
    return wordCount;
}

// Освобождение массива слов
void freeWords(char** words, int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

// Заполнение таблицы с возрастающими ключами
void fillTableAscending(SongTable* table, char** words, int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        addEntry(table, i + 1, words[i]);
    }
}

// Заполнение таблицы с убывающими ключами
void fillTableDescending(SongTable* table, char** words, int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        addEntry(table, wordCount - i, words[i]);
    }
}

// Заполнение таблицы со случайными ключами
void fillTableRandom(SongTable* table, char** words, int wordCount) {
    srand(time(NULL));
    for (int i = 0; i < wordCount; i++) {
        addEntry(table, rand() % (wordCount * 2) + 1, words[i]);
    }
}

// Изменение формата ключей
void changeKeyFormat(SongTable* table) {
    if (table->size == 0) {
        printf("Таблица пуста. Сначала загрузите песню.\n");
        return;
    }

    printf("Выберите новый формат ключей:\n");
    printf("1. По возрастанию\n");
    printf("2. По убыванию\n");
    printf("3. Случайные\n");
    printf("Ваш выбор: ");
    int keyType;
    scanf("%d", &keyType);

    if (keyType < 1 || keyType > 3) {
        printf("Неверный выбор.\n");
        return;
    }

    // Сохраняем текущие значения
    int currentSize = table->size;
    char** values = malloc(currentSize * sizeof(char*));
    if (!values) {
        perror("Ошибка выделения памяти");
        return;
    }

    for (int i = 0; i < currentSize; i++) {
        values[i] = table->entries[i].value;
    }

    // Очищаем таблицу (но не освобождаем значения, так как мы их сохранили)
    table->size = 0;

    // Заполняем с новыми ключами
    switch (keyType) {
        case 1:
            fillTableAscending(table, values, currentSize);
            break;
        case 2:
            fillTableDescending(table, values, currentSize);
            break;
        case 3:
            fillTableRandom(table, values, currentSize);
            break;
    }

    free(values);
    printf("Формат ключей успешно изменен.\n");
}

// Меню программы
void showMenu() {
    printf("\nМеню:\n");
    printf("1. Загрузить песню из файла\n");
    printf("2. Сортировать таблицу\n");
    printf("3. Найти слово по ключу\n");
    printf("4. Вывести таблицу\n");
    printf("5. Изменить формат ключей\n");
    printf("6. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    SongTable table;
    initTable(&table);
    
    char** words = NULL;
    int wordCount = 0;
    bool isSorted = false;
    int choice;
    
    do {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                // Загрузка песни из файла
                if (words) {
                    freeWords(words, wordCount);
                    freeTable(&table);
                    initTable(&table);
                }
                
                char filename[100];
                printf("Введите имя файла с песней: ");
                scanf("%99s", filename);
                
                wordCount = readWordsFromFile(filename, &words);
                if (wordCount == 0) {
                    printf("Не удалось прочитать слова из файла.\n");
                    break;
                }
                
                printf("Выберите тип ключей:\n");
                printf("1. По возрастанию\n");
                printf("2. По убыванию\n");
                printf("3. Случайные\n");
                printf("Ваш выбор: ");
                int keyType;
                scanf("%d", &keyType);
                
                switch (keyType) {
                    case 1:
                        fillTableAscending(&table, words, wordCount);
                        break;
                    case 2:
                        fillTableDescending(&table, words, wordCount);
                        break;
                    case 3:
                        fillTableRandom(&table, words, wordCount);
                        break;
                    default:
                        printf("Неверный выбор.\n");
                        break;
                }
                
                isSorted = (keyType == 1); // Если ключи по возрастанию, таблица уже отсортирована
                printf("Таблица успешно загружена. Всего слов: %d\n", wordCount);
                break;
            }
                
            case 2: {
                // Сортировка таблицы
                if (table.size == 0) {
                    printf("Таблица пуста. Сначала загрузите песню.\n");
                    break;
                }
                
                printf("\nИсходная таблица:\n");
                printTable(&table);
                
                shakerSort(&table);
                isSorted = true;
                
                printf("\nОтсортированная таблица:\n");
                printTable(&table);
                break;
            }
                
            case 3: {
                // Поиск по ключу
                if (table.size == 0) {
                    printf("Таблица пуста. Сначала загрузите песню.\n");
                    break;
                }
                
                if (!isSorted) {
                    printf("Таблица не отсортирована. Сначала выполните сортировку.\n");
                    break;
                }
                
                long key;
                printf("Введите ключ для поиска: ");
                scanf("%ld", &key);
                
                int index = binarySearch(&table, key);
                if (index != -1) {
                    printf("Найдено: ключ %ld -> слово \"%s\"\n", 
                           table.entries[index].key, table.entries[index].value);
                } else {
                    printf("Слово с ключом %ld не найдено.\n", key);
                }
                break;
            }
                
            case 4: {
                // Вывод таблицы
                if (table.size == 0) {
                    printf("Таблица пуста. Сначала загрузите песню.\n");
                    break;
                }
                
                printTable(&table);
                break;
            }
                
            case 5: {
                // Изменение формата ключей
                changeKeyFormat(&table);
                isSorted = false;
                break;
            }
                
            case 6: {
                // Выход
                printf("Завершение программы...\n");
                break;
            }
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    } while (choice != 6);
    
    // Освобождение памяти
    if (words) {
        freeWords(words, wordCount);
    }
    freeTable(&table);
    
    return 0;
}