CC=gcc
CFLAGS= -g -fPIC
LDFLAGS= 
LDLIBS= -L../ -lmalloc


.PHONY:all clean

all: test0 test1

test0: test0.c 
	${CC} -o test0 $^ ${CFLAGS} ${LDLIBS}

test1: test1.c 
	${CC} -o test1 $^ ${CFLAGS} ${LDLIBS}

clean:
	rm -f *~ *.o
	rm -f test0 test1
