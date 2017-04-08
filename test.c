// Test program to check how &* works.
// The macros in Arduino compose to
// form &* expressions.
#include <stdio.h>

static unsigned int mem = 5;
static unsigned int *addr; 

int main() {
  addr = &mem;
  printf("%04x\n", addr);
  printf("%04x\n", *addr);
  printf("%04x\n", &*addr);
}
