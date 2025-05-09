#include "pc_db.h"
#include "db_reader.h"

// Печать информации о компьютере в табличном формате
void print_computer(Computer pc) {
    const char* gpu_types[] = {"Integrated", "External", "Video Bus"};
    const char* os_names[] = {"Windows", "Linux", "MacOS", "Other"};
    
    printf("| %-15s | %2d | %-15s | %3d | %-10s | %2d | %-5s | %2d | %4d | %2d | %2d | %-10s |\n",
           pc.owner,
           pc.cpu_count,
           pc.cpu_type,
           pc.ram_size,
           gpu_types[pc.gpu_type],
           pc.vram_size,
           pc.hdd_type,
           pc.hdd_count,
           pc.hdd_capacity,
           pc.integrated_controllers,
           pc.peripheral_devices,
           os_names[pc.os]);
}

// Печать заголовка таблицы
void print_computer_table_header() {
    printf("+-----------------+----+-----------------+-----+------------+----+-------+----+------+----+----+------------+\n");
    printf("| Owner           | CP | CPU Type        | RAM | GPU Type   | VR | HDD   | HD | HDD  | IC | PD | OS         |\n");
    printf("|                 | Us |                 | (GB)|            |(GB)| Type  | #  | Cap. |    |    |            |\n");
    printf("+-----------------+----+-----------------+-----+------------+----+-------+----+------+----+----+------------+\n");
}

// Печать всей базы данных
void print_db(const char* filename) {
    DBReader* reader = db_reader_open(filename);
    if (!reader) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    print_computer_table_header();
    
    Computer pc;
    while (db_reader_read(reader, &pc)) {
        print_computer(pc);
    }
    
    printf("+-----------------+----+-----------------+-----+------------+----+-------+----+------+----+----+------------+\n");
    
    db_reader_close(reader);
}

// Проверка, является ли компьютер мультимедийным
bool is_multimedia(Computer pc) {
    // Мультимедийный компьютер имеет:
    // - внешнюю видеокарту с достаточным объемом памяти (>= 4GB)
    // - достаточно оперативной памяти (>= 8GB)
    // - хотя бы одно внешнее устройство (например, звуковая карта)
    return (pc.gpu_type == EXTERNAL || pc.gpu_type == VIDEO_BUS) && 
           pc.vram_size >= 4 && 
           pc.ram_size >= 8 && 
           pc.peripheral_devices > 0;
}

// Проверка, является ли компьютер бездисковой рабочей станцией
bool is_diskless(Computer pc) {
    // Бездисковая рабочая станция не имеет винчестеров
    // но имеет сетевую карту (интегрированный контроллер)
    return pc.hdd_count == 0 && pc.integrated_controllers > 0;
}

// Выполнение запроса к базе данных
void query_db(const char* filename, bool print_all, bool multimedia, bool diskless) {
    DBReader* reader = db_reader_open(filename);
    if (!reader) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    if (print_all) {
        print_db(filename);
        db_reader_close(reader);
        return;
    }
    
    if (multimedia) {
        printf("Multimedia computers:\n");
        print_computer_table_header();
    } else if (diskless) {
        printf("Diskless workstations:\n");
        print_computer_table_header();
    }
    
    Computer pc;
    while (db_reader_read(reader, &pc)) {
        if ((multimedia && is_multimedia(pc)) || (diskless && is_diskless(pc))) {
            print_computer(pc);
        }
    }
    
    printf("+-----------------+----+-----------------+-----+------------+----+-------+----+------+----+----+------------+\n");
    
    db_reader_close(reader);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <database_file> [-f] [-m] [-d]\n", argv[0]);
        printf("Options:\n");
        printf("  -f  Print all records\n");
        printf("  -m  Find multimedia computers\n");
        printf("  -d  Find diskless workstations\n");
        return 1;
    }
    
    const char* filename = argv[1];
    bool print_all = false;
    bool multimedia = false;
    bool diskless = false;
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            print_all = true;
        } else if (strcmp(argv[i], "-m") == 0) {
            multimedia = true;
        } else if (strcmp(argv[i], "-d") == 0) {
            diskless = true;
        }
    }
    
    if (!print_all && !multimedia && !diskless) {
        printf("No query parameters specified. Use -f, -m or -d.\n");
        return 1;
    }
    
    query_db(filename, print_all, multimedia, diskless);
    
    return 0;
}