CC = gcc
CFLAGS = -g -Wall -lncurses
LIBS = -lncurses

SOURCE_DIR_SHR=.

all:

clean:
	rm -f src/*.o

distclean:
	$(RM) -f config.status
	$(RM) -f *~
	$(RM) -f src/*~
	$(RM) -f configure.scan
	$(RM) -f autoscan.log
	$(RM) -f config.log
	$(RM) -rf autom4te.cache
