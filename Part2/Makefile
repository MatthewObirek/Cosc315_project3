COMP = g++
#COMP = gcc
FLAGS = -Wall -g -std=c++0x
#FLAGS = -Wall -g

all: Part2

myFileSystem.o: myFileSystem.hpp myFileSystem.cpp
	$(COMP) $(FLAGS) 

Part2: main.cpp myFileSystem.o myFileSystem.hpp
	$(COMP) $(FLAGS) -lpthread main.cpp myFileSystem.o -o $@

clean:
	rm -f Part*/mini-project*.o