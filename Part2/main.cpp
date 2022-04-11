#include "myFileSystem.hpp"


int main(int args, char** arg)
{
    myFileSystem FileSystem(arg[1]);


    FileSystem.createF((char*)"jeff", 8);

    FileSystem.ls();

    char* bufWrite = (char*)calloc(myFileSystem::blockSize, sizeof(char));
    char* bufRead = (char*)calloc(myFileSystem::blockSize, sizeof(char));

    strcpy(bufWrite, "hello");
    FileSystem.write((char*)"jeff", 0, bufWrite);
    std::cout<< "File written" << std::endl;
    FileSystem.read((char*)"jeff", 0, bufRead);
    std::cout << bufRead << std::endl;
    //FileSystem.deleteF((char*)"jeff");

    FileSystem.ls();

    return 0;
}