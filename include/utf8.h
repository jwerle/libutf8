
/**
 * libutf8  - `utf8.h'
 *
 * (c) 2013 joseph werle <joseph.werle@gmail.com>
 */

#ifndef UTF8_H
#define UTF8_H 1

#include <errno.h>

#if __GNUC__ >= 4
# define UTF8_EXTERN __attribute__((visibility("default")))
#else
# define UTF8_EXTERN
#endif

/**
 * Defines the maxium buffer length
 * for a encode/decode buffer
 */

#define UTF8_MAX_BUFFER_LENGTH 4096

/**
 * Tests whether `a' is in range of `b' and `c'
 */

#define UTF8_IN_URANGE(a,b,c) (a >= (unsigned int) b && a <= (unsigned int) c)

/**
 * Prints a utf8 encode/decode
 * error to `stderr' defaults to
 * `perror(str)'
 */

#define utf8_perror(str) {                                                     \
  switch (errno) {                                                             \
    case 0: break;                                                             \
    case UTF8E_EOF_BYTES_NEEDED:                                               \
      fprintf(stderr, "%s: (EOF_BYTES_NEEDED)\n", str);                        \
      break;                                                                   \
    case UTF8E_CODE_POINT_OOB:                                                 \
      fprintf(stderr, "%s: (CODE_POINT_OOB)\n", str);                          \
      break;                                                                   \
    case UTF8E_BYTE_RANGE:                                                     \
      fprintf(stderr, "%s: (BYTE_RANGE)\n", str);                              \
      break;                                                                   \
    case UTF8E_BYTE_BOUNDARY_RANGE:                                            \
      fprintf(stderr, "%s: (BYTE_BOUNDARY_RANGE)\n", str);                     \
      break;                                                                   \
    default: perror(str);                                                      \
  }                                                                            \
}

/**
 * Defines a set of error types
 */

typedef enum utf8_errors {
    UTF8E_EOF_BYTES_NEEDED = 1
  , UTF8E_CODE_POINT_OOB
  , UTF8E_BYTE_RANGE
  , UTF8E_BYTE_BOUNDARY_RANGE
} utf8_error_t;

/**
 * Returns a utf8 encoded string from
 * a given utf8 decoded string.
 *
 * Return value:
 *  Returns a `char *' or `NULL'
 *  in the case of an error.
 *
 * Error:
 *  In the occurence of an error
 *  `errno' will be populated with
 *  an error code which can be
 *  interpreted with `utf8_perror(str)'
 */

UTF8_EXTERN char *
utf8_encode (const char *);

/**
 * Returns a utf8 decoded string
 * from a given utf8 encoded string.
 *
 * Return value:
 *  Returns a `char *' or `NULL'
 *  in the case of an error.
 *
 * Error:
 *  In the occurence of an error
 *  `errno' will be populated with
 *  an error code which can be
 *  interpreted with `utf8_perror(str)'
 */

UTF8_EXTERN char *
utf8_decode (const char *);

#endif
