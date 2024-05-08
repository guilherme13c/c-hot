#pragma once

void *loadlib(const char *libpath);
void *getsymbol(void *libhandle, const char *symbol);
void closelib(void *libhandle);

#ifdef __linux__

#include <dlfcn.h>

void *loadlib(const char *libpath) { return dlopen(libpath, RTLD_NOW); }

void *getsymbol(void *libhandle, const char *symbol) {
    return dlsym(libhandle, symbol);
}

void closelib(void *libhandle) { dlclose(libhandle); }

#endif // __linux__

#ifdef _WIN32

#include <windows.h>

void *loadlib(const char *libpath) { return LoadLibrary(libpath); }

void *getsymbol(void *libhandle, const char *symbol) {
    return GetProcAddress(libhandle, symbol);
}

void closelib(void *libhandle) { FreeLibrary(libhandle); }

#endif // _WIN32
