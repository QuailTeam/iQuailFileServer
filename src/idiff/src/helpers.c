#include "helpers.h"

void write_copy(int fd_tgt, char *c)
{
  printf("%d\n", write(fd_tgt, "COPY: ", 6));
  printf("%d\n", write(fd_tgt, c, 1));
  printf("%d\n", write(fd_tgt, "\n", 1));
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
