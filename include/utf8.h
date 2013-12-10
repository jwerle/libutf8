
/**
 * libutf8  - `utf8.h'
 *
 * (c) 2013 joseph werle <joseph.werle@gmail.com>
 */

#ifndef __UTF8_H__
#define __UTF8_H__ 1

#if __GNUC__ >= 4
# define UTF8_EXTERN __attribute__((visibility("default")))
#else
# define UTF8_EXTERN
#endif

#define UTF8_MAX_BUFFER_LENGTH 512

/**
 * Returns a utf8 encoded string
 */

UTF8_EXTERN char *
utf8_encode (const char *string);

/**
 * Returns a utf8 decoded string
 */

UTF8_EXTERN char*
utf8_decode (const char *string);

#endif
