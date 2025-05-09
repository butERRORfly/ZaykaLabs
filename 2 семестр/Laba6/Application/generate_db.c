#include "pc_db.h"
#include "db_writer.h"


// Случайная генерация данных о компьютере
Computer generate_random_computer(int id) {
    Computer pc;
    
    // Генерация фамилии владельца
    snprintf(pc.owner, MAX_NAME_LEN, "Student%d", id);
    
    // Количество процессоров (1-2)
    pc.cpu_count = 1 + rand() % 2;
    
    // Тип процессора
    const char* cpu_types[] = {"Intel i5", "Intel i7", "AMD Ryzen 5", "AMD Ryzen 7"};
    strcpy(pc.cpu_type, cpu_types[rand() % 4]);
    
    // Объем памяти (4-32 ГБ)
    pc.ram_size = 4 + rand() % 29;
    
    // Тип видеоконтроллера
    pc.gpu_type = rand() % 3;
    
    // Объем видеопамяти (0-8 ГБ)
    pc.vram_size = (pc.gpu_type == INTEGRATED) ? 0 : 2 + rand() % 7;
    
    // Тип винчестера
    strcpy(pc.hdd_type, (rand() % 2) ? "SATA" : "SAS");
    
    // Количество винчестеров (0-2)
    pc.hdd_count = rand() % 3;
    
    // Ёмкость винчестеров (0, 256, 512, 1024 ГБ)
    const int capacities[] = {0, 256, 512, 1024};
    pc.hdd_capacity = capacities[rand() % 4];
    
    // Количество интегрированных контроллеров (1-5)
    pc.integrated_controllers = 1 + rand() % 5;
    
    // Количество внешних устройств (1-10)
    pc.peripheral_devices = 1 + rand() % 10;
    
    // Операционная система
    pc.os = rand() % 4;
    
    return pc;
}

// Генерация базы данных
void generate_db(const char* filename, int count) {
    DBWriter* writer = db_writer_open(filename);
    if (!writer) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    
    // Инициализация генерация рандом чисел (UNIX-текущее время NULL)
    srand(time(NULL));
    
    for (int i = 0; i < count; i++) {
        Computer pc = generate_random_computer(i + 1);
        db_writer_write(writer, pc);
    }
    
    db_writer_close(writer);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <output_file> <record_count>\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    int count = atoi(argv[2]);
    
    if (count < 20) {
        printf("Record count must be at least 20\n");
        return 1;
    }
    
    generate_db(filename, count);
    printf("Generated database with %d records in file '%s'\n", count, filename);
    
    return 0;
}