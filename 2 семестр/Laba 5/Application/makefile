CC = gcc  # компилятор
CFLAGS = -Wall -Wextra -std=c11  # Флаги компиляции:
                                 # -Wall - включить все предупреждения
                                 # -Wextra - дополнительные предупреждения
                                 # -std=c11 - стандарт C11

all: main_application

main_application: main.c kernel.h
	$(CC) $(CFLAGS) -o main_application main.c

clean:
	rm -f main_application

.PHONY: all clean test