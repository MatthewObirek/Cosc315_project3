#include "myFileSystem.hpp"

int main(int args, char** arg)
{
    myFileSystem FileSystem(arg[1]);


    FileSystem.createF((char*)"jeff", 8);

    FileSystem.ls();

    FileSystem.deleteF((char*)"jeff");

    FileSystem.ls();

    return 0;
}