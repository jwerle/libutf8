libutf8
=======

A whatwg compliant UTF8 encoding and decoding library based on this specification [http://encoding.spec.whatwg.org/](http://encoding.spec.whatwg.org/)

## install

***clib***:

```sh
$ clib install jwerle/libutf8
```

***source***:

```sh
$ make
$ make test
$ [sudo] make install
```

## usage

```c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <utf8.h>

int
main (void) {
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

  return 0;
}
```

## api

See [utf8.h](https://github.com/jwerle/libutf8/blob/master/utf8.h)

## license

MIT

