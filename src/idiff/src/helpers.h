#ifndef __HELPERS_
#define __HELPERS_

#include "bucket.h"
#include "stdio.h"

void write_insert(int fd_tgt, struct pair ret);
void write_copy(int fd_tgt, char *c);
unsigned int crc32 (const unsigned char *buf, int len, unsigned int init);

#endif /* end of include guard: __HELPERS_ */
