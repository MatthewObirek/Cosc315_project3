#COMP = g++
COMP = gcc
#FLAGS = -Wall -g -std=c++0x
FLAGS = -Wall -g

all: Part1.o #Part2.o

Part1.o: mini-project3.c
	$(COMP) $(FLAGS) mini-project3.c -lpthread -o $@

clean:
	rm -f *.o