commdir:=./include
incdir:=$(commdir)

VPATH:=$(incdir)

cc:=g++
CXXFLAGS:=-g -Wall -lpthread -I $(subst :, -I,$(incdir))
LDFLAGS:= -lrt

.PHONY:all clean

all:client server

client:client.o
	$(cc) -o client $^ $(LDFLAGS) $(CXXFLAGS) 
server:server.o
	$(cc) -o server $^ $(LDFLAGS) $(CXXFLAGS)

client.o:client.cpp common_shm.h common.h

server.o:server.cpp common_shm.h common.h my_hash.h my_locks.h

clean:
	-rm *.o client server
