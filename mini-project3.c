#include <stdio.h>
#include <stdlib.h>



char pageNumberN[5];
char virtualAddress[200];
char offsetN[5];
int offsetBits = 0;
FILE *readFile;


// this function reads a line from the file
// it is used to read the offset value and page number value from the file
void read_metadata_values(char* var){
    fgets(var,sizeof(var),readFile);
}

int main(int argc, char *argv[]){
	
    if(argc < 2){
        printf("Enter the file name in the args too\n");
        return 1;
    }

    // getting the file pointer of the input file from the arguments
    readFile = fopen(argv[1],"r");

    // calling the method two times to read the offset and page number to
    // store them in the declared variables
    read_metadata_values(offsetN);
    read_metadata_values(pageNumberN);

    // using atoi to convert offset string into int
    int temp = atoi(offsetN);

    // it is similar to pow function that takes the offset value and dose pow(2,offsetN)
    // and with this value I to vAddress & offsetBits that will give me only the offset from the vAddress
    int r = 1;
    for(;temp != 0;) {
        r *= 2;
        --temp;
    }
	offsetBits = r-1;
    

    // reading the file
	while (fgets(virtualAddress, sizeof(virtualAddress), readFile)) {
        
        // printing the values
        // here atoi is used to convert the string into int
        // atoi(virtualAddress) >> atoi(offsetN) right-shift the vAddress offset value times
        // atoi(virtualAddress) & offsetBits dose the and bitwise opreation to get the offset from vAddress
		printf("virtual address %d is in page number %d and offset %d\n",
        atoi(virtualAddress),atoi(virtualAddress) >> atoi(offsetN), atoi(virtualAddress) & offsetBits);
		
    }

	fclose(readFile);


	return 0;
}