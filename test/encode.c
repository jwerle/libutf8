
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utf8.h>
#include "common.h"

#define e(s) utf8_encode(s)

static char *
t (const char *str, const char *enc) {
  char *r = e(str);
  assert(0 == strcmp(enc, r));
  return r;
}

TEST(encode) {
  char *enc = NULL;
  char *tmp = NULL;
  unsigned char a[64];

  // 1 byte
  enc = e("\x5C");
  assert('\x5C' == enc[0]);

  enc = e("\x7F");
  assert('\x7F' == enc[0]);

  enc = e("\x0");
  assert('\0' == enc[0]);

  enc = e("\x1");
  assert('\x1' == enc[0]);

  enc = e("\x2");
  assert('\x2' == enc[0]);

  enc = e("\x2");
  assert('\x2' == enc[0]);

  enc = e("\x3");
  assert('\x3' == enc[0]);

  enc = e("\x4");
  assert('\x4' == enc[0]);

  enc = e("\x5");
  assert('\x5' == enc[0]);

  enc = e("\x6");
  assert('\x6' == enc[0]);

  enc = e("\x7");
  assert('\x7' == enc[0]);

  enc = e("\x8");
  assert('\x8' == enc[0]);

  enc = e("\x9");
  assert('\x9' == enc[0]);

  enc = e("\x0a");
  assert('\x0a' == enc[0]);

  enc = e("\x0b");
  assert('\x0b' == enc[0]);

  enc = e("\x0c");
  assert('\x0c' == enc[0]);

  enc = e("\x0d");
  assert('\x0d' == enc[0]);

  enc = e("\x0e");
  assert('\x0e' == enc[0]);

  enc = e("\x0f");
  assert('\x0f' == enc[0]);

  enc = e("\x21");
  assert('\x21' == enc[0]);

  enc = e("\x22");
  assert('\x22' == enc[0]);

  enc = e("\x23");
  assert('\x23' == enc[0]);

  enc = e("\x24");
  assert('\x24' == enc[0]);

  enc = e("\x25");
  assert('\x25' == enc[0]);

  enc = e("\x26");
  assert('\x26' == enc[0]);

  printf("encode: 1 byte ok\n");

  // 2 byte
  enc = e("\x80");
  assert('\xC2' == enc[0]);
  assert('\x80' == enc[1]);

  enc = e("\xa1");
  assert('\xc2' == enc[0]);
  assert('\xa1' == enc[1]);

  enc = e("\xa2");
  assert('\xc2' == enc[0]);
  assert('\xa2' == enc[1]);

  enc = e("\xa3");
  assert('\xc2' == enc[0]);
  assert('\xa3' == enc[1]);

  enc = e("\xa4");
  assert('\xc2' == enc[0]);
  assert('\xa4' == enc[1]);

  enc = e("\xa5");
  assert('\xc2' == enc[0]);
  assert('\xa5' == enc[1]);

  enc = e("\xa6");
  assert('\xc2' == enc[0]);
  assert('\xa6' == enc[1]);

  enc = e("\xa7");
  assert('\xc2' == enc[0]);
  assert('\xa7' == enc[1]);

  enc = e("\xa8");
  assert('\xc2' == enc[0]);
  assert('\xa8' == enc[1]);

  enc = e("\xa9");
  assert('\xc2' == enc[0]);
  assert('\xa9' == enc[1]);

  printf("encode: 2 byte ok\n");

  // 3 byte
  enc = t("𐌈", "ð");

  printf("encode: 3 byte ok\n");


  // interpolation
  // http://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt
  t("∮ E⋅da = Q,  n → ∞, ∑ f(i) = ∏ g(i)",
    "â® Eâda = Q,  n â â, â f(i) = â g(i)");


  t("∮ E⋅da = Q,  n → ∞, ∑ f(i) = ∏ g(i)",
    "â® Eâda = Q,  n â â, â f(i) = â g(i)");

  t("STARGΛ̊TE SG-1, a = v̇ = r̈, a⃑ ⊥ b⃑",
    "STARGÎÌTE SG-1, a = vÌ = rÌ, aâ â¥ bâ");


  printf("encode: interpolation ok\n");

  return 0;
}
