#include "db_reader.h"
#include <stdlib.h>

// Открытие DBReader
DBReader* db_reader_open(const char* filename) {
    DBReader* reader = (DBReader*)malloc(sizeof(DBReader));
    if (!reader) return NULL;
    
    reader->file = fopen(filename, "rb");
    if (!reader->file) {
        free(reader);
        return NULL;
    }
    
    return reader;
}

// Закрытие DBReader
void db_reader_close(DBReader* reader) {
    if (reader) {
        if (reader->file) {
            fclose(reader->file);
        }
        free(reader);
    }
}

// Чтение компьютера из базы данных
bool db_reader_read(DBReader* reader, Computer* pc) {
    if (!reader || !reader->file || !pc) return false;
    return fread(pc, sizeof(Computer), 1, reader->file) == 1;
}