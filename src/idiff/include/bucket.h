#ifndef __BUCKET_
#define __BUCKET_

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "uthash.h"

#define LEN 256 //length of the words hashed
#define BUFFER_LENGTH 4096 //length of buffer for comparison
#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

typedef struct entry {
  unsigned int key;
  off_t offset;
  UT_hash_handle hh;
} entry_t;

typedef struct pair {
  off_t off;
  int l;
} pair_t;

struct entry *find_entry(uint32_t addler_key);
int add_to_bucket(uint32_t addler_key, off_t offset);

#endif /* end of include guard: __BUCKET_ */
