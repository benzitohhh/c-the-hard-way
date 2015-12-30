PREFIX?=/usr/local

## Cygwin (assumes apr installed via cygwin):
CFLAGS=-g -Wall -I/usr/include/apr-1 -I/usr/include/apr-util-1
LDLIBS=-lapr-1 -pthread -laprutil-1

#### Hmmmm on Cygwin seems like we need to use LDLIBS rather than LDFLAGS
####   with LDFLAGS, -l options appear BEFORE the .o files, and the linker does not see them.
####   with LDLIBS, -l options appear AFTER the .o files, and the linker sees them ok

## OSX/linux (assumes apr installed manually in /usr/local/):
# CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1 -I${PREFIX}/apr/include/apr-util-1
# LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o command.o
## So the final compile line will look something like this:
##    cc -g -Wall  -lapr-1 -pthread -laprutil-1  devpkg.c bstrlib.o db.o shell.o command.o   -o devpkg
## Note how the .o files are linked statically, while apr/apr-util are linked dynamically

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -rf *.o
	rm -f devpkg
	rm -rf *.dSYM
