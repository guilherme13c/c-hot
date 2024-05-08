CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Wno-unused-variable -Wno-unused-result -O3 -Iinc -ltest -lpthread

$(shell mkdir -p bin lib obj)

testlib:
	buildlib.sh

build: src/main.c
	$(CC) src/main.c $(CFLAGS) -o bin/main

clean:
	rm -rf bin/* lib/* obj/*
