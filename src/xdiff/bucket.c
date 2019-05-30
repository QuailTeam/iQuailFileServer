#include "bucket.h"

struct entry *bucket = NULL;

void add_to_bucket(uint32_t hash_key, off_t offset) {
  struct entry *s;

  s = malloc(sizeof(struct entry));
  s->key = hash_key;
  s->offset = offset;
  HASH_ADD_INT(bucket, key, s);
}

struct entry *find_entry(uint32_t hash_key)
{
  struct entry *s;
  HASH_FIND_INT(bucket, &hash_key, s);
  return s;
}

unsigned int count_entries()
{
  return HASH_COUNT(bucket);
}
