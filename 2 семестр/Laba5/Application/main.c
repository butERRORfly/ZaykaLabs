#include "kernel.h"

// Инициализация таблицы
void initTable(SongTable* table) {
    table->entries = malloc(INITIAL_CAPACITY * sizeof(TableEntry));
    if (!table->entries) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }
    table->size = 0;
    table->capacity = INITIAL_CAPACITY;
}

// Увеличение емкости таблицы
void increaseCapacity(SongTable* table) {
    int new_capacity = table->capacity * 2;
    TableEntry* new_entries = realloc(table->entries, new_capacity * sizeof(TableEntry));
    if (!new_entries) {
        perror("Ошибка перевыделения памяти");
        exit(EXIT_FAILURE);
    }
    table->entries = new_entries;
    table->capacity = new_capacity;
}

// Добавление записи в таблицу
void addEntry(SongTable* table, long key, const char* value) {
    if (table->size == table->capacity) {
        increaseCapacity(table);
    }

    // Подсчет длины строки
    int len = 0;
    while (value[len] != '\0') {
        len++;
    }

    // Выделение памяти под строку
    table->entries[table->size].value = malloc(len + 1);
    if (!table->entries[table->size].value) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }

    // Копирование строки
    for (int i = 0; i <= len; i++) {
        table->entries[table->size].value[i] = value[i];
    }

    table->entries[table->size].key = key;
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

        for (int i = start; i < end; ++i) {
            if (table->entries[i].key > table->entries[i + 1].key) {
                swapEntries(&table->entries[i], &table->entries[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

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
int readWordsFromFile(const char* filename, SongTable* table) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return 0;
    }

    // Очищаем старую таблицу, если она была
    if (table->entries != NULL) {
        freeTable(table);
    }
    initTable(table);

    int wordCount = 0;
    char word[MAX_WORD_LENGTH];
    
    while (fscanf(file, "%99s", word) == 1) {
        // Удаляем знаки препинания из слова
        int len = 0;
        while (word[len] != '\0') {
            len++;
        }
        
        while (len > 0 && !isalpha(word[len - 1])) {
            word[len - 1] = '\0';
            len--;
        }
        
        if (len > 0) {
            addEntry(table, 0, word); // Ключ будет установлен позже
            wordCount++;
        }
    }
    
    fclose(file);
    return wordCount;
}

// Заполнение таблицы с возрастающими ключами
void fillTableAscending(SongTable* table) {
    for (int i = 0; i < table->size; i++) {
        table->entries[i].key = i + 1;
    }
}

// Заполнение таблицы с убывающими ключами
void fillTableDescending(SongTable* table) {
    for (int i = 0; i < table->size; i++) {
        table->entries[i].key = table->size - i;
    }
}

// Заполнение таблицы со случайными ключами
void fillTableRandom(SongTable* table) {
    srand(time(NULL));
    for (int i = 0; i < table->size; i++) {
        table->entries[i].key = rand() % (table->size * 2) + 1;
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
    if (scanf("%d", &keyType) != 1) {
        printf("Неверный ввод.\n");
        return;
    }

    switch (keyType) {
        case 1:
            fillTableAscending(table);
            break;
        case 2:
            fillTableDescending(table);
            break;
        case 3:
            fillTableRandom(table);
            break;
        default:
            printf("Неверный выбор.\n");
            return;
    }

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
    SongTable table = {0}; // Инициализируем нулями
    bool isSorted = false;
    int choice;
    
    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Неверный ввод. Попробуйте снова.\n");
            continue;
        }
        
        switch (choice) {
            case 1: {
                char filename[MAX_WORD_LENGTH];
                printf("Введите имя файла с песней: ");
                if (scanf("%99s", filename) != 1) {
                    printf("Ошибка чтения имени файла.\n");
                    break;
                }
                
                int wordCount = readWordsFromFile(filename, &table);
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
                if (scanf("%d", &keyType) != 1) {
                    printf("Неверный ввод.\n");
                    break;
                }
                
                switch (keyType) {
                    case 1:
                        fillTableAscending(&table);
                        isSorted = true;
                        break;
                    case 2:
                        fillTableDescending(&table);
                        isSorted = false;
                        break;
                    case 3:
                        fillTableRandom(&table);
                        isSorted = false;
                        break;
                    default:
                        printf("Неверный выбор.\n");
                        break;
                }
                
                printf("Таблица успешно загружена. Всего слов: %d\n", wordCount);
                break;
            }
                
            case 2: {
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
                if (scanf("%ld", &key) != 1) {
                    printf("Неверный ввод ключа.\n");
                    break;
                }
                
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
                if (table.size == 0) {
                    printf("Таблица пуста. Сначала загрузите песню.\n");
                    break;
                }
                
                printTable(&table);
                break;
            }
                
            case 5: {
                changeKeyFormat(&table);
                isSorted = false;
                break;
            }
                
            case 6: {
                printf("Завершение программы...\n");
                break;
            }
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    } while (choice != 6);
    
    freeTable(&table);
    return 0;
}