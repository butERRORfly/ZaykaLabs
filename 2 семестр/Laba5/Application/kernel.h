#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

const int MAX_WORD_LENGTH = 100;

typedef struct {
    long key;           // Ключ (8 байт)
    char* value;        // Значение (слово из песни)
} TableEntry;

typedef struct {
    TableEntry* entries;    // Динамический массив записей
    int size;               // Текущий размер таблицы
    int capacity;           // Вместимость таблицы
} SongTable;

// Инициализация таблицы
void initTable(SongTable* table);

// Увеличение емкости таблицы
void increaseCapacity(SongTable* table);

// Добавление записи в таблицу
void addEntry(SongTable* table, long key, const char* value);

// Освобождение памяти таблицы
void freeTable(SongTable* table);

// Печать таблицы
void printTable(const SongTable* table);

// Обмен двух записей таблицы
void swapEntries(TableEntry* a, TableEntry* b);

// Сортировка шейкером
void shakerSort(SongTable* table);

// Двоичный поиск по ключу
int binarySearch(const SongTable* table, long key);

// Чтение слов из файла
int readWordsFromFile(const char* filename, char*** words);

// Освобождение массива слов
void freeWords(char** words, int count);

// Заполнение таблицы с возрастающими ключами
void fillTableAscending(SongTable* table, char** words, int wordCount);

// Заполнение таблицы с убывающими ключами
void fillTableDescending(SongTable* table, char** words, int wordCount);

// Заполнение таблицы со случайными ключами
void fillTableRandom(SongTable* table, char** words, int wordCount);

// Изменение формата ключей
void changeKeyFormat(SongTable* table);

// Меню программы
void showMenu();

// Собственные реализации функций string.h
size_t my_strlen(const char* str);
char* my_strdup(const char* str);
int my_strcmp(const char* s1, const char* s2);

#endif // KERNEL_H