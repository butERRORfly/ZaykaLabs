#ifndef DB_READER_H
#define DB_READER_H

#include "pc_db.h"

// Структура для чтения базы данных
typedef struct {
    FILE* file;
} DBReader;

// Функции для работы с базой данных
DBReader* db_reader_open(const char* filename);
void db_reader_close(DBReader* reader);
bool db_reader_read(DBReader* reader, Computer* pc);

#endif // DB_READER_H