
#include <stdio.h>
#include "common.h"

int
main (void) {
  printf("\nlibutf8: running tests\n\n");

  T(encode);
  T(decode);

  printf("\nlibutf8: all tests ok!\n");
  return 0;
}
