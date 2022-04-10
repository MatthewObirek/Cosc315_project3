#include <iostream>
#include <stdint.h>
#include <string.h>


class myFileSystem
{
private:

public:
    myFileSystem(std::string diskName);
    
    int createF(char name[8], int32_t size);
    int deleteF(char name[8]);

    int ls(void);
    
    int read(char name[8], int32_t blockNum, char buf[1024]);
    int write(char name[8], int32_t blockNum, char buf[1024]);

};