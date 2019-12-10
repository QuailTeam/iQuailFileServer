#include "helpers.h"

void write_copy(int fd_tgt, char *c)
{
  write(fd_tgt, "COPY: ", 6);
  write(fd_tgt, c, 1);
  write(fd_tgt, "\n", 1);
}

void write_insert(int fd_tgt, struct pair ret)
{
  char buff_off[21];
  char buff_len[12];

  sprintf(buff_off, "%li", ret.off);
  sprintf(buff_len, "%u", ret.l);
  write(fd_tgt, "INSERT: ", 8);
  write(fd_tgt, buff_off, strlen(buff_off));
  write(fd_tgt, " LEN ", 5);
  write(fd_tgt, buff_len, strlen(buff_len));
  write(fd_tgt, "\n", 1);
}

off_t strdiff(const char *s1, const char *s2, off_t max)
{
  off_t i = 0;
  for (i=0; i < max && s1[i] == s2[i] ; i++);
  return i;
}
