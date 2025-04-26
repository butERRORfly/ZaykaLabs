#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define INITIAL_CAPACITY 11

typedef struct {
    long key;
    char* value;
} TableEntry;

typedef struct {
    TableEntry* entries;
    int size;
    int capacity;
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
int readWordsFromFile(const char* filename, SongTable* table);

// Заполнение таблицы с возрастающими ключами
void fillTableAscending(SongTable* table);

// Заполнение таблицы с убывающими ключами
void fillTableDescending(SongTable* table);

// Заполнение таблицы со случайными ключами
void fillTableRandom(SongTable* table);

// Изменение формата ключей
void changeKeyFormat(SongTable* table);

// Меню программы
void showMenu();

#endif // KERNEL_H