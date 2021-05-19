#include <cstdio>

int main() {
  const int max_name = 80;
  char name[max_name];

  char fmt[10];
  sprintf(fmt, "%%%ds", max_name - 1);
  printf("%s\n", fmt);
  scanf(fmt, name);
  printf("%s\n", name);
}