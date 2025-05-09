#include "db_writer.h"
#include <stdlib.h>

// Открытие DBWriter
DBWriter* db_writer_open(const char* filename) {
    DBWriter* writer = (DBWriter*)malloc(sizeof(DBWriter));
    if (!writer) return NULL;
    
    writer->file = fopen(filename, "wb");
    if (!writer->file) {
        free(writer);
        return NULL;
    }
    
    return writer;
}

// Закрытие DBWriter
void db_writer_close(DBWriter* writer) {
    if (writer) {
        if (writer->file) {
            fclose(writer->file);
        }
        free(writer);
    }
}

// Запись компьютера в базу данных
void db_writer_write(DBWriter* writer, Computer pc) {
    if (writer && writer->file) {
        fwrite(&pc, sizeof(Computer), 1, writer->file);
    }
}