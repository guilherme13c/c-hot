#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct filestate;

void watchfile(struct filestate *fs, void **args);
time_t filelastmod(char *filename);

#ifdef __linux__

#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>

struct filestate {
    char *path;
    time_t lastmodified;
    pthread_mutex_t *mutex;
    pthread_t *th;
};

void *__watchfile(void *arg) {
    

    void **args = (void **)arg;

    struct filestate *fs = (struct filestate *)args[0];

    void (*handler)(void **) = (void (*)(void **))args[1];
    void **handlerargs = (void **)args[2];

    fs->lastmodified = -1;
    time_t current_lastmodified = -1;

    while (1) {
        pthread_mutex_lock(fs->mutex);

        current_lastmodified = filelastmod(fs->path);

        if (current_lastmodified != -1 && current_lastmodified !=
            fs->lastmodified) {
            handler(handlerargs);

            fs->lastmodified = current_lastmodified;
        }
        pthread_mutex_unlock(fs->mutex);

        sleep(1); // Sleep for 1 s
    }
}

void watchfile(struct filestate *fs, void **args) {
    if (pthread_mutex_init(fs->mutex, NULL) != 0) {
        perror("Mutex initialization failed.\n");
        return;
    }

    if (pthread_create(fs->th, NULL, __watchfile, (void *)args) != 0) {
        perror("Thread creation failed.\n");
        return;
    }
}

time_t filelastmod(char *filename) {
    struct stat fileinfo;

    if (stat(filename, &fileinfo) != 0) {
        perror("Failed to get file stats.\n");
        return -1;
    }

    return fileinfo.st_mtime;
}

#endif // __linux__
