CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: generate_db query_db

generate_db: generate_db.c pc_db.h
	$(CC) $(CFLAGS) -o generate_db generate_db.c

query_db: query_db.c pc_db.h
	$(CC) $(CFLAGS) -o query_db query_db.c

clean:
	rm -f generate_db query_db computers.db

test: generate_db query_db
	./generate_db computers.db 25
	./query_db computers.db -f
	./query_db computers.db -m
	./query_db computers.db -d

.PHONY: all clean test