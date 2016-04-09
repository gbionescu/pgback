#ifndef UTIL_D_H
#define UTIL_D_H
#include <stdio.h>
#include <typeinfo>

#define cppprint(...) printf("[%s] ", typeid(this).name()); printf(__VA_ARGS__);
#define cprint(...) printf("[%s] ", __FILE__); printf(__VA_ARGS__);

#endif
