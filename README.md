# Cosc315_project3

The make file runs this line of code, which is translated into this line of bash

`$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@` -> `$(COMP) $(FLAGS) Part1/mini-project3.c -lpthread -o Part1/$@`

---

## Group Members & Division of Tasks

Monica Rampaul: Documentation
Matthew Obirek: Part 2
Manson Yu: Part 1

---

## Part 1

### Run Instructions:
To run the program, either use this: `cd Part1` - > `./mini-project3 input.txt`
or:  `./Part1/mini-project3 Part1/input.txt`

### Explanation & Design Choices:
This implementation uses two functions: `read_metadata_values` as well as a `main` function. 

`read_metadata_values` reads in a textfile line by line. It's purpose is to read the offset value and the page number that is defined in `input.txt`. This function is used within the `main` function. 

The `main` function first checks for the correct number of arguments when the program runs as it requires a file to read from. If the additional file is not specified, the program notifies the user that they must enter the file to be read from and terminates the program by returning 1. Otherwise, the `main` function opens the read stream for the textfile by getting the file pointer using `fopen()`. Then, the function calls the `read_metadata_values` function twice in order to get the offset value and page number from the textfile and store them in global char variables. The offset value is then converted into an int datatype using `atoi()` since it will be needed for calculations in order to get the offset for the virtual address. Next, a while loop is used in order to read the remainder of the textfile and print the approprate information. Finally, the file stream is closed using `fclose()`. 

### Sample Output:
```
(base) MacBook-Pro:Part1 monicarampaul$ ./mini-project3 input.txt 
virtual address 11235 is in page number 2 and offset 3043 
virtual address 33215 is in page number 8 and offset 447 
virtual address 55535 is in page number 13 and offset 2287
```

---

## Part 2

