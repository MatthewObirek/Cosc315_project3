#COMP = g++
COMP = gcc
#FLAGS = -Wall -g -std=c++0x
FLAGS = -Wall -g

all: mini-project3.o

mini-project3.o: Part1/mini-project3.c
	$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@

clean:
	rm -f Part*/mini-project*.o