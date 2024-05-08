# cDog

cDog is a simple header only library for hotreloading dynamic libraries in C and C++. The library is composed by 2 modules: watchdog.h and hotdog.h. The first contains utilities for watching files and executing callback funtions whenever they are altered, and the second one is an abstraction layer for operating system specific syscalls for loading dynamic linking libraries during runutime.

## How to use

1. Download the files [hotdog.h](https://github.com/guilherme13c/cDog/blob/main/inc/hotdog.h) and [watchdog.h](https://github.com/guilherme13c/cDog/blob/main/inc/watchdog.h) from the `inc/` folder of this repository.

2. Include the files in your program:

    ```C
    #include "hotdog.h"
    #include "watchdog.h"
    ...
    ```

3. Create the filestate for the file you want to watch:

    ```C
    int main(void) {
        struct filestate fs;
        pthread_mutex_t lib_mutex;
        fs.mutex = &lib_mutex;
        pthread_t lib_watchdog_th;
        fs.th = &lib_watchdog_th;
        fs.path = "lib/libtest.so";
    
    ...
    }
    ```
4. Create global definitions for the signature of the callback function and for the symbols from the dynamic library. Also create variables to hold the libhandle and the symbols:

    ```C
    void lib_watchdog_handler(void *args);

    typedef void (*printmsgSymbol)(char *);

    printmsgSymbol printmsg;
    void *libhandle;

    int main(void) {
        ...
    }
    ```
5. Define the callback function. In the test case we use the functions `closelib`, `loadlib` and `getsymbol`:

    ```C
    void lib_watchdog_handler(void *args) {
        void **arg_list = (void **)args;

        system("./buildlib.sh;");

        if (libhandle != NULL) {
            closelib(libhandle);
        }
        libhandle = loadlib("lib/libtest.so");
        printmsg = (printmsgSymbol)getsymbol(libhandle, "printmsg");

        return;
    }
    ```

6. Add the flag `-lpthread` to you compilation command, since the `watchdog.h` file depends on it.

    ```Makefile
    CC = gcc
    CFLAGS = -Wall -Wextra -std=c17 -Wno-unused-variable -Wno-unused-result -O3 -Iinc -ltest -lpthread
    ```

7. Adjust your program to use the mutex from the file state. This is important to avoid race conditions and loss of the library state:

    ```C
    ...

    while (1) {
        sleep(1);
        pthread_mutex_lock(&lib_mutex);

        printmsg("Test\n");

        pthread_mutex_unlock(&lib_mutex);
    }

    pthread_mutex_destroy(&lib_mutex);

    ...
    ```
