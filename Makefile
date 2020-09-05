CC=g++

INCLUDE_DIR=inc
SRC=$(wildcard src/*.cc)

OBJS=$(SRC:.cc=.o)

CFLAGS=-I$(INCLUDE_DIR) -std=c++17 -Wall


all: 
	$(CC) $(CFLAGS) $(OBJS) -o pervertt 

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $< 