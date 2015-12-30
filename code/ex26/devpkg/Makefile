PREFIX?=/usr/local

# On cywin, apr installed via cygwin installer in /usr/lib, /usr/include... (so no need for extra flags)
# CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1   -I${PREFIX}/apr/include/apr-util-1
# LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1
CFLAGS=-g -Wall
LDFLAGS=-lapr-1 -pthread -laprutil-1

# On OSX/linux, apr installed manually:
# CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1   -I${PREFIX}/apr/include/apr-util-1
# LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o command.o

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -rf *.o
	rm -f devpkg
	rm -rf *.dSYM
