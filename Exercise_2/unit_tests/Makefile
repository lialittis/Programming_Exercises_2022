commdir:=../include
incdir:=$(commdir)

VPATH:=$(incdir)

cc:=g++
CXXFLAGS:=-g -Wall -lpthread -I $(incdir)

.PHONY:all clean

all:hash_test threads_test

hash_test:hash_test.cpp
	$(cc) -o hash_test $^ $(CXXFLAGS)
threads_test:threads_test.cpp 
	$(cc) -o threads_test $^ $(CXXFLAGS)

clean:
	-rm *test
