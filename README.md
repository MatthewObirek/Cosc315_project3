# Cosc315_project3


The make file runs this line of code, which is translated into this line of bash

`$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@` -> `$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@`

## Part 1
To run the program, use this either: `cd Part1` - > `./mini-project3.o input.txt`
or:  `./Part1/mini-project3.o Part1/input.txt`