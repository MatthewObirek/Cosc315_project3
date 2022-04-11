#include <iostream>
#include <stdint.h>
#include <string.h>
#include <fstream>

struct inode 
{
    char name[8]; //file name
    int32_t size; // file size (in number of blocks)

    int32_t blockPointers[8]; // direct block pointers
    int32_t used;// 0 => inode is free; 1 => in use
};


class myFileSystem
{
public:
    const static int blockSize = 1024;
    const static int blockCount = 128;
    const static int maxFileSize = 8;
    const static int maxNumFiles = 16;

private:
    char* buffer;
    std::fstream disk;
    char freeBlockList[blockCount];
    inode inodeIndex[maxNumFiles];              //initialzed with calloc in constructor;


public:
    myFileSystem(const char* diskName);
    ~myFileSystem();
    
    int createF(char name[8], int32_t size);
    int deleteF(char name[8]);

    int ls(void);
    
    int read(char name[8], int32_t blockNum, char buf[1024]);
    int write(char name[8], int32_t blockNum, char buf[1024]);

};