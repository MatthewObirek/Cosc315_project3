#COMP = g++
COMP = gcc
#FLAGS = -Wall -g -std=c++0x
FLAGS = -Wall -g

all: Part1.o #Part2.o

Part1.o: Part1/mini-project3.c
	$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@

#Part2.o: Part1/mini-project3.c
#	$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@

clean:
	rm -f Part*/mini-project*.o