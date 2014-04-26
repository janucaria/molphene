#ifndef __molphene__logger__
#define __molphene__logger__

#include <cstdio>

#define LOG_D(fmt, ...) printf(fmt "\n", __VA_ARGS__)
#define LOG_I(fmt, ...) printf(fmt "\n", __VA_ARGS__)
#define LOG_W(fmt, ...) printf(fmt "\n", __VA_ARGS__)
#define LOG_E(fmt, ...) printf(fmt "\n", __VA_ARGS__)

#endif /* defined(__molphene__logger__) */
