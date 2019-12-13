#ifndef LIBIDIFF
#define LIBIDIFF
#include <stddef.h>

int computeDelta(char const *src, char const *tgt, char const *patch, size_t max_memory);
int patchDelta(char const *src, char const *patch, char const *tgt);

#endif /* end of include guard:  */
