
/**
 * libutf8 - `encode.c'
 *
 * (c) 2013 joseph werle <joseph.werle@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <utf8.h>

char *
utf8_encode (const char *str) {
  // encoded char buffer
  unsigned char buf[UTF8_MAX_BUFFER_LENGTH];

  // code pointer pointer
  unsigned char cp = 0;

  // byte for encoded bytes
  unsigned char b = 0;

  // code point value
  unsigned int c = 0;

  // stream index
  int i = 0;

  // encoded buffer index
  int n = 0;

  // byte count
  int count = 0;

  // byte offset
  int offset = 0;

  while ('\0' != (cp = (str[i++]))) {
    if (errno > 0) {
      return NULL;
    }

    c = (unsigned int) cp;

    if (UTF8_IN_URANGE(c, 0xD800, 0xDFFF)) {
      errno = UTF8E_CODE_POINT_OOB;
      break;
    }

    if (EOF == c) {
      buf[n++] = EOF;
      break;
    }

    if (UTF8_IN_URANGE(c, 0x0000, 0x07F)) {
      buf[n++] = c;
      continue;
    }

    if (UTF8_IN_URANGE(c, 0x0080, 0x07FF)) {
      count = 1;
      offset = 0xC0;
    } else if (UTF8_IN_URANGE(c, 0x0800, 0xFFFF)) {
      count = 2;
      offset = 0xE0;
    } else if (UTF8_IN_URANGE(c, 0x10000, 0x10FFFF)) {
      count = 3;
      offset = 0xF0;
    }

    buf[n++] = (c/pow(64, count)) + offset;

    while (count > 0) {
      b = c/pow(64, count - 1);
      buf[n++] = 0x80 + (b % 64);
      count--;
    }
  }

  buf[n] = '\0';

  return strdup((char *)buf);
}
