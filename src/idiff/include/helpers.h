#ifndef __HELPERS_
#define __HELPERS_

#define ERROR_READ -1
#define ERROR_WRITE -2
#define ERROR_MALLOC -3

#include "bucket.h"
#include "stdio.h"

void write_insert(int fd_tgt, struct pair ret);
void write_copy(int fd_tgt, char *c);
unsigned int crc32 (const unsigned char *buf, int len, unsigned int init);
off_t strdiff(const char *, const char *, off_t);
#endif /* end of include guard: __HELPERS_ */
