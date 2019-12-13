#include "bucket.h"
#include "helpers.h"

/*This small library is a small differential compression library
  It first calculates a hash table, before comparing the hashes of the target
  file to the source file.
  initMatch -> findMatch -> expand_right (-> expand_left)
*/

int initMatch(int fd, size_t max_memory) {
  char buff[LEN];
  unsigned int crc32_value;
  off_t i = 0;
  off_t file_size = lseek(fd, 0L, SEEK_END);
  ssize_t read_bytes;
  size_t used_memory = 0;
  lseek(fd, 0L, SEEK_SET);
  while((used_memory < max_memory) && ((i + LEN) <= file_size)) {
    read_bytes = read(fd, buff, LEN);
    crc32_value = crc32(buff, read_bytes, 0);
    if(find_entry(crc32_value) == NULL)
      if(add_to_bucket(crc32_value, i) == -1)
        return ERROR_MALLOC;
    i += LEN;
    used_memory += sizeof(entry_t);
  }
}

int expand_right(int fd_src, int fd_tgt, int offset_src)
{
  off_t len = 0;
  off_t tmp_len = 0;
  ssize_t read_bytes;
  ssize_t total_read;
  off_t max_len = 0;
  char buff_src[BUFFER_LENGTH];
  char buff_tgt[BUFFER_LENGTH];

  // loop reading a buffer a data and comparing them. If the buffers are

  lseek(fd_src, offset_src, SEEK_SET);
  do {
  max_len = min(read(fd_src, buff_src, BUFFER_LENGTH), \
  (read_bytes = read(fd_tgt, buff_tgt, BUFFER_LENGTH)));
  if (max_len == -1)
    return ERROR_READ;
  tmp_len = strdiff(buff_src, buff_tgt, max_len);
  len += tmp_len;
  total_read += read_bytes;
} while(tmp_len == BUFFER_LENGTH);
  lseek(fd_tgt, -total_read, SEEK_CUR);
  return len;
}


/*Expand left is currently unused. This will somewhat reduce the compression
Needs to be fixed */

int expand_left(int fd_src, int fd_tgt, int offset_src)
{
  int len = 0;
  int max_len = 0;
  off_t offset_tgt = lseek(fd_tgt, 0, SEEK_CUR);
  char buff_src[LEN];
  char buff_tgt[LEN];

  if (offset_src < LEN || offset_tgt < LEN)
    return len;
  lseek(fd_tgt, -LEN, SEEK_CUR);
  lseek(fd_src, offset_src - LEN, SEEK_SET);
  max_len = min(read(fd_src, buff_src, LEN), read(fd_tgt, buff_tgt, LEN));
  if (max_len < LEN)
    return len;
  while(max_len && buff_src[max_len - 1] == buff_tgt[max_len -1])
    max_len--;
  lseek(fd_tgt, LEN, SEEK_CUR);
  return LEN - max_len;
}

pair_t findMatch(int fd_src, int fd_tgt, int fd_patch) {
  char buff[LEN];
  int back_track = 0;
  entry_t *s;
  pair_t ret;
  int read_bytes;
  if((read_bytes = read(fd_tgt, buff, LEN)) < LEN)
      buff[read_bytes] = 0;
  if(read_bytes == -1) {
    ret.off = ERROR_READ;
    ret.l = ERROR_READ;
  }
  s = find_entry(crc32(buff, read_bytes, 0));
  lseek(fd_tgt, -read_bytes, SEEK_CUR);
  if (s == NULL) {
    ret.off = -1;
    ret.l = 0;
    return ret;
  }
  ret.off = s->offset;
  ret.l = expand_right(fd_src, fd_tgt, ret.off);
  return ret;
}


int computeDelta(char const *src, char const *tgt,
                 char const *patch, size_t max_memory) {
  off_t position = 0;
  char c;
  const mode_t perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int fd_src = open(src, O_RDONLY);
  int fd_tgt = open(tgt, O_RDONLY);
  int fd_patch = open(patch, O_RDWR | O_CREAT, perm);
  int file_size = lseek(fd_tgt, 0L, SEEK_END);
  pair_t f_ret;

  if (fd_src == -1 || fd_tgt == -1 || fd_patch == -1)
    return ERROR_OPEN;
  lseek(fd_tgt, 0L, SEEK_SET); //Technically not needed, this is more done for safety sake
  if (initMatch(fd_src, max_memory) == -1)
    return ERROR_MALLOC;
  while (position < file_size) {
    f_ret = findMatch(fd_src, fd_tgt, fd_patch);
    if (f_ret.off == ERROR_READ && f_ret.l == ERROR_READ)
      return ERROR_READ;
    if (f_ret.l < LEN) {
      if(!read(fd_tgt, &c, 1))
        return -1;
      write_copy(fd_patch, &c);
      position++;
    }
    else {
      write_insert(fd_patch, f_ret);
      position += f_ret.l;
      lseek(fd_tgt, f_ret.l, SEEK_CUR);
    }
  }
  close(fd_src);
  close(fd_tgt);
  close(fd_patch);
  return 0;
}
