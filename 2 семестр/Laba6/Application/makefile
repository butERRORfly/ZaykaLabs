CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: generate_db query_db

generate_db: generate_db.c pc_db.h db_writer.h db_writer.c
	$(CC) $(CFLAGS) -o generate_db generate_db.c db_writer.c

query_db: query_db.c pc_db.h db_reader.h db_reader.c
	$(CC) $(CFLAGS) -o query_db query_db.c db_reader.c

clean:
	rm -f generate_db query_db computers.db

test: generate_db query_db
	./generate_db computers.db 25
	./query_db computers.db -f
	./query_db computers.db -m
	./query_db computers.db -d

.PHONY: all clean test