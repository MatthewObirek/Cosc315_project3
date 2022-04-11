# Cosc315_project3

---

## Group Members & Division of Tasks

Monica Rampaul: Testing and Documentation
Matthew Obirek: Part 2
Manson Yu: Part 1

---

## Part 1

### Build and Run Instructions:
to Build the program, change to the Part1 directory by running `cd Part1` in the main `Cosc315_project3` directory. Then run `make`. To run the program, inside the Part1 directory, run `./Part1.o input.txt`


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

### Build and Run Instructions:
to Build the program, change to the Part2 directory by running `cd Part2` in the main `Cosc315_project3` directory. Then run `mkdir out`, and then `make`. To run the program, inside the Part2 directory build disk0: `./create_fs.o disk`, then run `./out/Part2 disk0`


### Sample output
```
[matthewobirek@MatthewPC Part2]$ ./out/Part2 disk0
(Constructor) freeBlockList Initialized

(createF) File: file1.c Size: 3 Created!

(createF) File: file2.c Size: 8 Created!

(createF) File: file3.c Size: 4 Created!

(createF) File: a.out Size: 5 Created!

(createF) File: lab1.jav Size: 6 Created!

(List)
|_file1.c       3kB
|_file2.c       8kB
|_file3.c       4kB
|_a.out 5kB
|_lab1.jav      6kB

(CommandSwitch) What would you like to write? hellkadfg
(CommandSwitch) What would you like to write? sdghdfh
(CommandSwitch) What would you like to write? dfh
(CommandSwitch) What would you like to write? dfhfd
(CommandSwitch) What would you like to write? gds
(CommandSwitch) What would you like to write? a
(CommandSwitch) What would you like to write? sdaf
(CommandSwitch) What would you like to write? afg
(CommandSwitch) What would you like to write? dfg
(CommandSwitch) What would you like to write? sdh
(CommandSwitch) What would you like to write? sdghs
(CommandSwitch) What would you like to write? fg
(CommandSwitch) What would you like to write? sdgsdg
(deleteF) File: file3.c Deleted.
 
(CommandSwitch) buffer read from: file1.c at Personal inodeBlock: 2
Buffer: dfh

(createF) File: file4.c Size: 7 Created!

(List)
|_file1.c       3kB
|_file2.c       8kB
|_file4.c       7kB
|_a.out 5kB
|_lab1.jav      6kB

(CommandSwitch) buffer read from: file2.c at Personal inodeBlock: 4
Buffer: sdaf

(CommandSwitch) buffer read from: file2.c at Personal inodeBlock: 5
Buffer: afg

(CommandSwitch) buffer read from: file2.c at Personal inodeBlock: 6
Buffer: 

(deleteF) File: lab1.jav Deleted.

(createF) File: lab2.jav Size: 7 Created!

(CommandSwitch) buffer read from: a.out at Personal inodeBlock: 1
Buffer: sdh

(CommandSwitch) buffer read from: a.out at Personal inodeBlock: 3
Buffer: fg

(CommandSwitch) buffer read from: a.out at Personal inodeBlock: 0
Buffer: dfg

(List)
|_file1.c       3kB
|_file2.c       8kB
|_file4.c       7kB
|_a.out 5kB
|_lab2.jav      7kB

(Destructor) Closing File System
```