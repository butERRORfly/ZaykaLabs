#ifndef PC_DB_H
#define PC_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Константы для размеров строковых полей
#define MAX_NAME_LEN 50
#define MAX_CPU_TYPE_LEN 20
#define MAX_GPU_TYPE_LEN 20
#define MAX_HDD_TYPE_LEN 10
#define MAX_OS_LEN 30

// Тип видеоконтроллера
typedef enum {
    INTEGRATED,     // Встроенный
    EXTERNAL,       // Внешний
    VIDEO_BUS       // Видео-шина
} GpuType;

// Тип операционной системы
typedef enum {
    WINDOWS,
    LINUX,
    MACOS,
    OTHER_OS
} OsType;

// Структура для хранения информации о ПЭВМ
typedef struct {
    char owner[MAX_NAME_LEN];          // Фамилия владельца
    int cpu_count;                     // Количество процессоров
    char cpu_type[MAX_CPU_TYPE_LEN];   // Тип процессора
    int ram_size;                      // Объем памяти (в ГБ)
    GpuType gpu_type;                  // Тип видеоконтроллера
    int vram_size;                     // Объем видеопамяти (в ГБ)
    char hdd_type[MAX_HDD_TYPE_LEN];   // Тип винчестера (SAS/SATA)
    int hdd_count;                     // Количество винчестеров
    int hdd_capacity;                  // Ёмкость винчестеров (в ГБ)
    int integrated_controllers;        // Количество интегрированных контроллеров
    int peripheral_devices;            // Количество внешних устройств
    OsType os;                         // Операционная система
} Computer;

// Функции для работы с базой данных
void print_computer(Computer pc);
void print_computer_table_header();
void generate_db(const char* filename, int count);
void print_db(const char* filename);
void query_db(const char* filename, bool print_all, bool multimedia, bool diskless);

#endif // PC_DB_H