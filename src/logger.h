#ifndef __molphene__logger__
#define __molphene__logger__

#include <cstdio>

#define LOG_D(fmt, ...) \
  printf(fmt " on %s:%i\n", __VA_ARGS__, __FILE__, __LINE__)
#define LOG_I(fmt, ...) \
  printf(fmt " on %s:%i\n", __VA_ARGS__, __FILE__, __LINE__)
#define LOG_W(fmt, ...) \
  printf(fmt " on %s:%i\n", __VA_ARGS__, __FILE__, __LINE__)
#define LOG_E(fmt, ...) \
  printf(fmt " on %s:%i\n", __VA_ARGS__, __FILE__, __LINE__)

#endif
