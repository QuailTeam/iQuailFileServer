#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "uthash-master/src/uthash.h"

#define LEN 16 //length of the words hashed
#define BUFFER_LENGTH 4096 //length of buffer for comparison
#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

struct entry {
  unsigned int key;
  off_t offset;
  UT_hash_handle hh;
};

struct pair {
  off_t off;
  int l;
};

struct entry *find_entry(uint32_t addler_key);
void add_to_bucket(uint32_t addler_key, off_t offset);
