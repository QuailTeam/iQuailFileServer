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
  int len = 0;
  int max_len = 0;
  char buff_src[BUFFER_LENGTH];
  char buff_tgt[BUFFER_LENGTH];

  lseek(fd_src, offset_src, SEEK_SET);
  max_len = min(read(fd_src, buff_src, BUFFER_LENGTH), read(fd_tgt, buff_tgt, BUFFER_LENGTH));
  while(len % BUFFER_LENGTH <= max_len && !strncmp(buff_src, buff_tgt, len % BUFFER_LENGTH) )
  {
    len++;
    if (len % BUFFER_LENGTH == 0)
    {
      if(read(fd_src, buff_src, BUFFER_LENGTH) < BUFFER_LENGTH || read(fd_tgt, buff_tgt, BUFFER_LENGTH) < BUFFER_LENGTH)
        break;
    }
  }
  lseek(fd_tgt, -((len / BUFFER_LENGTH + 1) * BUFFER_LENGTH) + len, SEEK_CUR);
  return len;
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

struct pair findMatch(int fd_src, int fd_tgt, int fd_patch) {
  char buff[LEN];
  int back_track = 0;
  struct entry *s;
  struct pair ret;

  read(fd_tgt, buff, LEN);
  s = find_entry(crc32(buff, LEN, 0));
  lseek(fd_tgt, -LEN, SEEK_CUR);
  if (s == NULL) {
    ret.off = -1;
    ret.l = -1;
    return ret;
  }
  ret.off = s->offset;
  ret.l = expand_right(fd_src, fd_tgt, ret.off);
  /*if( back_track = expand_left(fd_src, fd_tgt, ret.off))
  {
    lseek(fd_patch, -back_track * 8, SEEK_CUR);
    ret.off -= back_track;
    ret.l +=back_track;
  }*/
  return ret;
}


int computeDelta(char *src, char* tgt, char* patch) {
  off_t i = 0;
  char c[1];
  int fd_src = open(src, O_RDONLY);
  int fd_tgt = open(tgt, O_RDONLY);
  int fd_patch = open(patch, O_RDWR || O_CREAT);
  int file_size = lseek(fd_tgt, 0L, SEEK_END);
  struct pair f_ret;

  lseek(fd_tgt, 0L, SEEK_SET);
  initMatch(fd_src);
  while (i < file_size) {
    f_ret = findMatch(fd_src, fd_tgt, fd_patch);
    if (f_ret.l < LEN) {
      read(fd_tgt, c, 1);
      write_copy(fd_patch, c);
      i += 1;
    }
    else {
      write_insert(fd_patch, f_ret);
      i += f_ret.l;
    }
  }
}
