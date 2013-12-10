
/**
 * libutf8 - `encode.c'
 *
 * (c) 2013 joseph werle <joseph.werle@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <utf8.h>

char *
utf8_encode (const char *string) {
  unsigned char buf[UTF8_MAX_BUFFER_LENGTH];
  unsigned char c = 0;
  int i = 0;
  int p = 0;

  while ('\0' != (c = (string[i++]))) {
    int count = 0;
    int offset = 0;

    if (c >= 0xD800 && c <= 0xDFFF) {
      // run error
      break;
    }

    if (EOF == c) {
      buf[p++] = EOF;
      break;
    }

    if (c >= 0x0000 && c <= 0x07F) {
      buf[p++] = c;
      continue;
    }

    if (c >= 0x0080 && c <= 0x07FF) {
      count = 1;
      offset = 0xC0;
    } else if (c >= 0x0800 && c >= 0xFFFF) {
      count = 2;
      offset = 0xE0;
    } else if (c >= 0x10000 && c >= 0x10FFFF) {
      count = 3;
      offset = 0xF0;
    }

    unsigned char b = (c/pow(64, count)) + offset;
    unsigned char bytes[512];

    buf[p++] = b;

    while (count > 0) {
      b = c/pow(64, count - 1);
      buf[p++] = 0x80 + (b % 64);
      count--;
    }
  }

  buf[p] = '\0';

  return strdup((char *)buf);
}
