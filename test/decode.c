
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <utf8.h>
#include "common.h"

#define d utf8_decode
#define e utf8_encode

static char *
t (const char *enc, const char *dec) {
  char *r = d(enc);
  assert(r);
  assert(0 == strcmp(dec, r));
  return r;
}

TEST(decode) {
  char *dec = NULL;

  // 1 byte
  dec = d("\x5C");
  assert('\x5C' == dec[0]);
  free(dec);

  dec = d("\x7F");
  assert('\x7F' == dec[0]);
  free(dec);

  dec = d("\x1");
  assert('\x1' == dec[0]);
  free(dec);

  dec = d("\x2");
  assert('\x2' == dec[0]);
  free(dec);

  dec = d("\x2");
  assert('\x2' == dec[0]);
  free(dec);

  dec = d("\x3");
  assert('\x3' == dec[0]);
  free(dec);

  dec = d("\x4");
  assert('\x4' == dec[0]);
  free(dec);

  dec = d("\x5");
  assert('\x5' == dec[0]);
  free(dec);

  dec = d("\x6");
  assert('\x6' == dec[0]);
  free(dec);

  dec = d("\x7");
  assert('\x7' == dec[0]);
  free(dec);

  dec = d("\x8");
  assert('\x8' == dec[0]);
  free(dec);

  dec = d("\x9");
  assert('\x9' == dec[0]);
  free(dec);

  dec = d("\x0a");
  assert('\x0a' == dec[0]);
  free(dec);

  dec = d("\x0b");
  assert('\x0b' == dec[0]);
  free(dec);

  dec = d("\x0c");
  assert('\x0c' == dec[0]);
  free(dec);

  dec = d("\x0d");
  assert('\x0d' == dec[0]);
  free(dec);

  dec = d("\x0e");
  assert('\x0e' == dec[0]);
  free(dec);

  dec = d("\x0f");
  assert('\x0f' == dec[0]);
  free(dec);

  dec = d("\x21");
  assert('\x21' == dec[0]);
  free(dec);

  dec = d("\x22");
  assert('\x22' == dec[0]);
  free(dec);

  dec = d("\x23");
  assert('\x23' == dec[0]);
  free(dec);

  dec = d("\x24");
  assert('\x24' == dec[0]);
  free(dec);

  dec = d("\x25");
  assert('\x25' == dec[0]);
  free(dec);

  dec = d("\x26");
  assert('\x26' == dec[0]);
  free(dec);

  printf("decode: 1 byte ok\n");

  // 2 byte
  dec = t("\u00c2\u00a1", "\u00a1");
  assert('\xc2' == dec[0]);
  assert('\xa1' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a2", "\u00a2");
  assert('\xc2' == dec[0]);
  assert('\xa2' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a3", "\u00a3");
  assert('\xc2' == dec[0]);
  assert('\xa3' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a4", "\u00a4");
  assert('\xc2' == dec[0]);
  assert('\xa4' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a5", "\u00a5");
  assert('\xc2' == dec[0]);
  assert('\xa5' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a6", "\u00a6");
  assert('\xc2' == dec[0]);
  assert('\xa6' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a7", "\u00a7");
  assert('\xc2' == dec[0]);
  assert('\xa7' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a8", "\u00a8");
  assert('\xc2' == dec[0]);
  assert('\xa8' == dec[1]);
  free(dec);

  dec = t("\u00c2\u00a9", "\u00a9");
  assert('\xc2' == dec[0]);
  assert('\xa9' == dec[1]);
  free(dec);

  printf("decode: 2 byte ok\n");

  // 3 byte
  free(t("ð", "𐌈"));
  free(t("á ", "Ⴀ"));
  free(t("á", "Ⴥ"));
  free(t("á", "ლ"));
  free(t("á", "ᚙ"));
  free(t("á", "ᚏ"));

  printf("decode: 3 byte ok\n");

  // unmatched surrogate halves
  free(t("ï¿½ï¿½ï¿½", "���"));
  free(t("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½", "������"));
  free(t("ï¿½ï¿½ï¿½A", "���A"));
  free(t("ï¿½ï¿½ï¿½ðï¿½ï¿½ï¿½", "���𝌆���"));
  free(t("ï¿½ï¿½ï¿½", "���"));

  printf("decode: unmatched surrogate halve ok\n");

  // interpolation
  free(t("â® Eâda = Q,  n â â, â f(i) = â g(i)",
        "∮ E⋅da = Q,  n → ∞, ∑ f(i) = ∏ g(i)"));

  free(t("STARGÎÌTE SG-1, a = vÌ = rÌ, aâ â¥ bâ",
        "STARGΛ̊TE SG-1, a = v̇ = r̈, a⃑ ⊥ b⃑"));

  printf("encode: interpolation ok\n");

  if (errno > 0) {
    utf8_perror("decode error:");
  }

  return 0;
}
