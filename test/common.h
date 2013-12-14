
#ifndef UTF8_TEST_H
#define UTF8_TEST_H 1

#include <assert.h>

#define UTF8_STRINGIFY_HELPER(x) #x
#define UTF8_STRINGIFY(x) UTF8_STRINGIFY_HELPER(x)

#define D(name) int utf8_test_##name ();

#define T(name) { \
  printf("%s: checking..\n", UTF8_STRINGIFY(name)); \
  assert(0 == utf8_test_##name ()); \
  printf("%s: pass\n", UTF8_STRINGIFY(name)); \
}

#define TEST(name) int utf8_test_##name ()

D(encode)
D(decode)

#endif
