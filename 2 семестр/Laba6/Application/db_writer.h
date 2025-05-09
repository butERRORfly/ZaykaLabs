#ifndef DB_WRITER_H
#define DB_WRITER_H

#include "pc_db.h"

// Структура для записи в базу данных
typedef struct {
    FILE* file;
} DBWriter;

// Функции для работы с базой данных
DBWriter* db_writer_open(const char* filename);
void db_writer_close(DBWriter* writer);
void db_writer_write(DBWriter* writer, Computer pc);

#endif // DB_WRITER_H