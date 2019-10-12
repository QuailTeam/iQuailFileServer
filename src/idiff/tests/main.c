int computeDelta(char *src, char* tgt, char* patch);

int main(int ac, char **av)
{
  computeDelta(av[1], av[2], av[3]);
  return 0;
}
