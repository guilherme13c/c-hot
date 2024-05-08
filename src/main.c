#include "watchdog.h"
#include "hotdog.h"

void lib_watchdog_handler(void *args);

typedef void (*printmsgSymbol)(char *);

printmsgSymbol printmsg;
void *libhandle;

int main(void) {
    struct filestate fs;
    pthread_mutex_t lib_mutex;
    fs.mutex = &lib_mutex;
    pthread_t lib_watchdog_th;
    fs.th = &lib_watchdog_th;
    fs.path = "lib/libtest.so";

    void *lib_watchdog_handler_args[] = {};
    void *args[] = {&fs, lib_watchdog_handler, lib_watchdog_handler_args};
    watchfile(&fs, args);

    while (1) {
        sleep(1);
        pthread_mutex_lock(&lib_mutex);

        printmsg("Test");

        pthread_mutex_unlock(&lib_mutex);
    }

    pthread_mutex_destroy(&lib_mutex);

    return 0;
}

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
