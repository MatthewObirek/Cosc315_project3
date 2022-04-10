COMP = g++
#COMP = gcc
FLAGS = -Wall -g -std=c++0x
#FLAGS = -Wall -g

all: myFileSystem.o Part2

myFileSystem.o: myFileSystem.hpp myFileSystem.cpp
	$(COMP) -c myFileSystem.cpp -o $@

Part2: main.cpp myFileSystem.o myFileSystem.hpp
	$(COMP) $(FLAGS) -lpthread main.cpp myFileSystem.o -o out/$@

clean:
	rm -f *.o