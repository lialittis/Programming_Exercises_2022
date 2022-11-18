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

client.o:client.cpp

server.o:server.cpp

clean:
	-rm *.o client server
