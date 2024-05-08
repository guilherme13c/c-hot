# cDog

cDog is a simple header only library for hotreloading dynamic libraries in C and C++. The library is composed by 2 modules: watchdog.h and hotdog.h. The first contains utilities for watching files and executing callback funtions whenever they are altered, and the second one is an abstraction layer for operating system specific syscalls for loading dynamic linking libraries during runutime.
