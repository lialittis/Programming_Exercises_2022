CC=gcc
CFLAGS= -Wall -g -fPIC
LDFLAGS= -lm
LDLIBS=
	 
libmalloc.so: my_malloc.c my_malloc.h
		${CC} -shared -o libmalloc.so $^ ${CFLAGS} ${LDFLAGS}
		 
clean:
		rm -f *~ *.o
		rm -f libmalloc.so
# end
