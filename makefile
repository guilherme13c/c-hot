CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Wno-unused-variable -O3 -Iinc -ltest -lc -lpthread

lib: src/test_lib.c
	$(CC) $(CFLAGS) -fPIC -c src/test_lib.c -o obj/test_lib.o
	$(CC) -shared obj/test_lib.o -o lib/libtest.so
	LD_LIBRARY_PATH=lib
	export LD_LIBRARY_PATH
	sudo cp lib/libtest.so /usr/local/lib
	sudo ldconfig

build: src/main.c
	$(CC) src/main.c $(CFLAGS) -o bin/main

clean:
	rm -rf bin/* lib/* obj/*
