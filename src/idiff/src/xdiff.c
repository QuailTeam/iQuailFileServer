#include "bucket.h"
#include "helpers.h"

void initMatch(int fd) {
  char buff[LEN];
  unsigned int crc32_value;
  off_t i = 0;
  off_t file_size = lseek(fd, 0L, SEEK_END);

  lseek(fd, 0L, SEEK_SET);
  while(i + LEN <= file_size) {
    read(fd, buff, LEN);
    crc32_value = crc32(buff, LEN, 0);
    if(find_entry(crc32_value) == NULL)
      add_to_bucket(crc32_value, i);
    i += LEN;
  }
}

int expand_right(int fd_src, int fd_tgt, int offset_src)
{
  off_t len = 0;
  off_t read_bytes;
  off_t max_len = 0;
  char buff_src[BUFFER_LENGTH];
  char buff_tgt[BUFFER_LENGTH];

  lseek(fd_src, offset_src, SEEK_SET);
  max_len = min(read(fd_src, buff_src, BUFFER_LENGTH), (read_bytes=read(fd_tgt, buff_tgt, BUFFER_LENGTH)));
  lseek(fd_tgt, -read_bytes, SEEK_CUR);
  return strdiff(buff_src, buff_tgt, max_len);
}

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
  s = find_entry(crc32(buff, read_bytes, 0));
  lseek(fd_tgt, -read_bytes, SEEK_CUR);
  if (s == NULL) {
    ret.off = -1;
    ret.l = -1;
    return ret;
  }
  ret.off = s->offset;
  ret.l = expand_right(fd_src, fd_tgt, ret.off);
  return ret;
}


int computeDelta(char const *src, char const *tgt, char const *patch) {
  off_t position = 0;
  char c;
  const mode_t perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int fd_src = open(src, O_RDONLY);
  int fd_tgt = open(tgt, O_RDONLY);
  int fd_patch = open(patch, O_RDWR | O_CREAT, perm);
  int file_size = lseek(fd_tgt, 0L, SEEK_END);
  pair_t f_ret;

  lseek(fd_tgt, 0L, SEEK_SET);
  initMatch(fd_src);
  while (position < file_size) {
    f_ret = findMatch(fd_src, fd_tgt, fd_patch);
    if (f_ret.l < LEN) {
      read(fd_tgt, &c, 1);
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
