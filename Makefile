
OS = $(shell uname)
CC ?= gcc
AR = ar
LD = ld
LN = ln
RM = rm
VALGRIND ?= valgrind
STRIP = strip
PREFIX ?= /usr/local
DESTDIR ?= utf8
VERSION_MAJOR = 0
VERSION_MINOR = 1
LIB_NAME = utf8
TARGET_NAME = lib$(LIB_NAME)
TARGET_STATIC = $(TARGET_NAME).a
TARGET_DSOLIB = $(TARGET_NAME).so.$(VERSION_MAJOR).$(VERSION_MINOR)
TARGET_DYLIB = $(TARGET_NAME).$(VERSION_MAJOR).$(VERSION_MINOR).dylib
TARGET_DSO = $(TARGET_NAME).so
CFLAGS ?= -Iinclude -std=c99 -Wall -fvisibility=hidden -O2 -fPIC -pedantic
LDFLAGS ?= -shared -soname $(TARGET_DSO).$(VERSION_MAJOR)
OSX_LDFLAGS ?= -lc -Wl,-install_name,$(TARGET_DSO), -o $(TARGET_DSOLIB)
SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
TEST_SRC = $(filter-out test/test.c, $(wildcard test/*.c))
TEST_OBJS = $(TEST_SRC:.c=.o)
TEST_MAIN = utf8-test

ifdef DEBUG
	CFLAGS += -DUTF8_DEBUG
endif

all: $(TARGET_STATIC) $(TARGET_DSO)

$(TARGET_STATIC): clean $(OBJS)
	$(AR) crus $(TARGET_STATIC) $(OBJS)

$(TARGET_DSO): clean $(OBJS)
ifeq ("Darwin","$(OS)")
	$(CC) -shared $(OBJS) $(OSX_LDFLAGS) -o $(TARGET_DSOLIB)
	$(LN) -s $(TARGET_DSOLIB) $(TARGET_DSO)
	$(LN) -s $(TARGET_DSOLIB) $(TARGET_DSO).$(VERSION_MAJOR)
else
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET_DSOLIB)
	$(LN) -s $(TARGET_DSOLIB) $(TARGET_DSO)
	$(LN) -s $(TARGET_DSOLIB) $(TARGET_DSO).$(VERSION_MAJOR)
	$(STRIP) --strip-unneeded $(TARGET_DSO)
endif

src/.c.o:
	$(CC) $(CFLAGS) -c $<

test/.c.o:
	$(CC) $(CFLAGS) -c $<

check: test
	$(VALGRIND) --leak-check=full ./$(TEST_MAIN)

test: $(TEST_OBJS)
	$(CC) $(TEST_OBJS) test/test.c ./$(TARGET_STATIC) $(CFLAGS) -o $(TEST_MAIN)
	./$(TEST_MAIN)

clean:
	$(RM) -f $(TEST_MAIN)
	$(RM) -f $(OBJS)
	$(RM) -f $(TEST_OBJS)
	$(RM) -f $(TARGET_STATIC)
	$(RM) -f $(TARGET_DSOLIB)
	$(RM) -f $(TARGET_DSO).$(VERSION_MAJOR)
	$(RM) -f $(TARGET_DSO)
	$(RM) -f $(TARGET_DYLIB)

install:
	test -d $(PREFIX)/$(DESTDIR) || mkdir $(PREFIX)/$(DESTDIR)
	install include/$(LIB_NAME).h $(PREFIX)/include/$(DESTDIR)
	install $(TARGET_STATIC) $(PREFIX)/lib
	install $(TARGET_DSO) $(PREFIX)/lib

uninstall:
	rm -rf $(PREFIX)/$(DESTDIR)
	rm -f $(PREFIX)/lib/$(TARGET_STATIC)
	rm -f $(PREFIX)/lib/$(TARGET_DSO)

.PHONY: test
