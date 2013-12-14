
#include <stdio.h>
#include <string.h>
#include <utf8.h>
#include "common.h"

int
main (void) {
  printf("\nlibutf8: running tests\n\n");

  T(encode);
  T(decode);

  char str[] = "Foo © bar 𝌆 baz ☃ qux";
  char *enc = NULL; 
  char *dec = NULL;

  enc = utf8_encode(str);

  if (NULL == enc) {
    utf8_perror("encode");
    return 1;
  }

  dec = utf8_decode(enc);

  if (NULL == dec) {
    utf8_perror("decode");
    return 1;
  }

  assert(0 == strcmp(str, dec));

  printf("\nlibutf8: all tests ok!\n");
  return 0;
}
