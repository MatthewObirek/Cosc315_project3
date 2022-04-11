#include "myFileSystem.hpp"


int main(int args, char** arg)
{
    if(args < 2)
    {
        std::cout << "Please enter diskName as arg" << std::endl;
        return 1;
    }
    myFileSystem FileSystem(arg[1]);
    
    std::ifstream input;
    input.open("lab3input.txt", std::ios::in);
    for(std::string line; std::getline(input,line); )
    {
        char* temp = new char[line.length() +1];
        strcpy(temp, line.c_str());
        char* strptr = strtok(temp, " ");
        
        char command;
        char* file;
        int size;
        
        int i = 0;
        while(strptr != nullptr)
        {
            if(i == 0) //assign Command
                command = strptr[0];
            else if(i == 1) // collect file name
                file = strptr;
            else if(i == 2) // collect size or position of file
                size = (int)(strptr[0])-48;

            i++;
            strptr = strtok(nullptr, " ");
        }
        char* tempBuffer = (char*)calloc(myFileSystem::blockSize, sizeof(char));
        switch(command)
        {
        case 'C': 
            FileSystem.createF(file, size);
        break;
        case 'D':
            FileSystem.deleteF(file);
        break;
        case 'L':
            FileSystem.ls();
        break;
        case 'R':
            FileSystem.read(file, size, tempBuffer);
            std::cout <<"(CommandSwitch) buffer read from: " << file << " at Personal inodeBlock: " << size << std::endl;
            std::cout <<"Buffer: "<< tempBuffer <<std::endl;
        break;
        case 'W':
            std::cout << "(CommandSwitch) What would you like to write? ";
            std::cin >> tempBuffer;
            FileSystem.write(file, size, tempBuffer);
        break;
        case 'd':
        break;
        default:
            std::cout << "[Error]:(CommandSwitch) Impropper Command read: " << command << std::endl;
        }

        std::cin.get();
        //std::cout << std::endl << line << std::endl << std::endl;
    }



    /*
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
    */
    return 0;
}