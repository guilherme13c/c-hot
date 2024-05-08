#!/bin/bash

gcc -Wall -Wextra -std=c17 -Wno-unused-variable -Wno-unused-result -O3 -Iinc -ltest -lc -lpthread -fPIC -c src/test_lib.c -o obj/test_lib.o
gcc -shared obj/test_lib.o -o lib/libtest.so
LD_LIBRARY_PATH=lib
export LD_LIBRARY_PATH
sudo cp lib/libtest.so /usr/local/lib
sudo ldconfig
