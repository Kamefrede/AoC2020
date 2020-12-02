#include "aocutil.h"
#include <stdlib.h>

FILE* ensure_open(const char *path, const char *mode) {
  FILE* f = fopen(path, mode);
  if (!f) {
    perror("Error opening file");
    exit(1);
  }
  return f;
}
