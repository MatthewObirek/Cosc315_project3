#pragma once
#include "myFileSystem.hpp"


myFileSystem::myFileSystem(const char* diskName)
{
  // Open the file with name diskName
  disk.open(diskName, std::ios::in | std::ios::out);
  // Read the first 1KB and parse it to structs/objecs representing the super block
  if(!disk.is_open())
  {
    std::cout << "[Error]:(Constructor) diskName: False, Please try again." << std::endl;
  }
  else
  {
    buffer = (char*)calloc(blockSize, sizeof(char));
    disk.readsome(buffer, blockSize);
    // freeBlockList init
    for(int i = 0; i < blockCount; i++)
    {
      freeBlockList[i] = buffer[i];
    } 
    std::cout << "(Constructor) freeBlockList Initialized" << std::endl;
    // Making sure that the superblock is accounted for.
    if(freeBlockList[0] != 1)
      freeBlockList[0] = 1;


    // 	An easy way to work with the 1KB memory chunk is to move a pointer to a
    //	position where a struct/object begins. You can use the sizeof operator to help
    //	cleanly determine the position. Next, cast the pointer to a pointer of the
    //	struct/object type.
    
    // loading in inodes
    int i = blockCount;
    for(int j = 0; j < maxNumFiles; j++)
    {
      char temp[sizeof(inode)];
      for(int k = 0; k < sizeof(inode); k++)
      { 
        temp[k] = buffer[i+k];
      }
      
      inode* tempInode = (inode*)temp;
      inodeIndex[j] = *tempInode;
      i+=sizeof(inode);
    }

    free(buffer);
  }
  // Be sure to close the file in a destructor or otherwise before
  // the process exits.
}

myFileSystem::~myFileSystem()
{
  // Be sure to close the file in a destructor or otherwise before
  std::cout << "(Destructor) Closing File System" << std::endl;
  // the process exits.
  disk.close();
}


int myFileSystem::createF(char name[8], int32_t size)
{ 
  //create a file with this name and this size

  // high level pseudo code for creating a new file

  // Step 1: Look for a free inode by searching the collection of objects
  // representing inodes within the super block object.
  // If none exist, then return an error.
  // Also make sure that no other file in use with the same name exists.
  if(!(size <= maxFileSize))
  {
    std::cout << "[Error]:(createF) Size to big, max size: " << maxFileSize << ", Given Size: " << size << std::endl;
    return -1;
  }
  int index = -1;
  int i;
  for(i = 0; i < maxNumFiles; i++)
  {
    if ((strncmp(inodeIndex[i].name, name, 8) == 0) && (inodeIndex[i].used > 0))
    {
      std::cout << "[Error]:(createF) File name taken: " << name << std::endl;
      return -1;
    }

    if ((int)inodeIndex[i].used == 0)
    {
      index = i;
      break;
    }
  }
 
  if(i > 15)
  {
    std::cout << "[Error]:(createF) disk is full" << std::endl;
    return -1;
  }
  // Step 2: Look for a number of free blocks equal to the size variable
  // passed to this method. If not enough free blocks exist, then return an error.
  int blockIndexArray[size];
  int k = 0;
  for(int j = 0; j < blockCount; j++)
  {
    if(freeBlockList[j] == 0)
    {
      blockIndexArray[k] = j;
      k++;
    }
    if(k == size)
      break;
  }
  if(k < size-1)
  {
    std::cout << "[Error]:(createF) not enough space" << std::endl;
    return -1;
  }
  // Step 3: Now we know we have an inode and free blocks necessary to
  // create the file. So mark the inode and blocks as used and update the rest of
  // the information in the inode
  strcpy(inodeIndex[index].name, name);
  inodeIndex[index].size = size;
  inodeIndex[index].used = 1;
  for(int j = 0; j < size; j++)
  {
    freeBlockList[blockIndexArray[j]] = 1;
    inodeIndex[index].blockPointers[j] = blockIndexArray[j];
  }
  // Step 4: Write the entire super block back to disk.
  //	An easy way to do this is to seek to the beginning of the disk
  //	and write the 1KB memory chunk.
  buffer = (char*)calloc(blockSize, sizeof(char));
  char* inodeIndexPointer = (char*)&inodeIndex;
  for(int n = 0; n < blockSize; n++)
  {
    if(n < blockCount)
      buffer[n] = freeBlockList[n];
    if(n >= blockCount && n < (sizeof(inode)*maxNumFiles + blockCount))
    {
      buffer[n] = inodeIndexPointer[n-blockCount];
    }      
  }

  disk.seekp(0, std::ios::beg);
  disk.write(buffer, blockSize);
  std::cout << "(createF) File: "<< inodeIndex[index].name << " Size: " << inodeIndex[index].size << " Created!" << std::endl; 
  
  return 0;
} // End Create



int myFileSystem::deleteF(char name[8])
{
  // Delete the file with this name

  // Step 1: Look for an inode that is in use with given name
  // by searching the collection of objects
  // representing inodes within the super block object.
  // If it does not exist, then return an error.
  int index = -1;
  for(int n = 8; n>0;n--)
  {
    
    for(int i = 0; i < maxNumFiles; i++)
    {
      if(strncmp(inodeIndex[i].name, name, n) == 0)
      {
        index = i;
        break;
      }

    }
    if(index != -1)
      break;
  }

  if(index == -1)
  {
    {
      std::cout << "[Error]:(deleteF) no file found by the name of: " << name << std::endl;
      return -1;
    }
  }
  // Step 2: Free blocks of the file being deleted by updating
  // the object representing the free block list in the super block object.
  for(int j = 0; j < inodeIndex[index].size; j++)
  {
    freeBlockList[inodeIndex[index].blockPointers[j]] = 0;
    inodeIndex[index].blockPointers[j] = 0;
  }
  //
  // Step 3: Mark inode as free.


  //inodeIndex[index].name
  inodeIndex[index].size = 0;
  inodeIndex[index].used = 0;
  //Step 4: Write the entire super block back to disk.
  buffer = (char*)calloc(blockSize, sizeof(char));
  char* inodeIndexPointer = (char*)&inodeIndex;
  for(int n = 0; n < blockSize; n++)
  {
    if(n < blockCount)
      buffer[n] = freeBlockList[n];
    if(n >= blockCount && n < (sizeof(inode)*maxNumFiles + blockCount))
    {
      buffer[n] = inodeIndexPointer[n-blockCount];
    }
         
  }



  disk.seekp(0, std::ios::beg);
  disk.write(buffer, blockSize);
  std::cout << "(deleteF) File: "<< inodeIndex[index].name <<" Deleted."  << std::endl;
  return 0;
} // End Delete


int myFileSystem::ls(void)
{ 
  // List names of all files on disk
  std::cout << "(List)" << std::endl;

  // Step 1: Print the name and size fields of all used inodes.
  for(int i = 0; i < maxNumFiles; i++)
  {
    if(inodeIndex[i].used > 0)
      std::cout << "|_" << inodeIndex[i].name << "\t" << inodeIndex[i].size << "kB" << std::endl;
  }
  return 0;
} // End ls

int myFileSystem::read(char name[8], int32_t blockNum, char buf[1024])
{

  // read this block from this file
  // Return an error if and when appropriate. For instance, make sure
  // blockNum does not exceed size-1.

  // Step 1: Locate the inode for this file as in Step 1 of delete.
  int index = -1;
  for(int i = 0; i < maxNumFiles;  i++)
  {
    if(inodeIndex[i].used > 0)
    {
      if(strncmp(inodeIndex[i].name, name, 8) == 0)
      {
        index = i;
      }
    }
  }
  
  if(index == -1)
  {
    std::cout << "[Error]:(Read) No file with name: " << name << std::endl;
    return -1;
  }

  if(blockNum >= inodeIndex[index].size)
  {
    std::cout << "[Error]:(Read) blockNum is greater than  " << inodeIndex[index].size-1 <<": "<< blockNum<< std::endl;    
    return -1;
  }
  
  // Step 2: Seek to blockPointers[blockNum] and read the block
  // from disk to buf.
  char* tempBuf  = (char*)calloc(blockSize, sizeof(char));
  disk.seekg((inodeIndex[index].blockPointers[blockNum]*blockSize),std::ios::beg);
  disk.readsome(tempBuf, blockSize);
  strcpy(buf, tempBuf);
  return 0;
} // End read 

int myFileSystem::write(char name[8], int32_t blockNum, char buf[1024])
{

  // write this block to this file
  // Return an error if and when appropriate.
  // Step 1: Locate the inode for this file as in Step 1 of delete.
  int index = -1;
  for(int i = 0; i < maxNumFiles; i++)
  {
    if(inodeIndex[i].used > 0)
    {
      if(strncmp(inodeIndex[i].name, name, 8) == 0)
      {
        index = i;
      }
    }
  }
  if(index == -1)
  {

    std::cout << "[Error]:(Write) No file with name: " << name << std::endl;
    return -1;
  }
    if(blockNum >= inodeIndex[index].size)
  {
    std::cout << "[Error]:(Write) blockNum is greater than "<<inodeIndex[index].size-1<<": " << name << std::endl;    
    return -1;
  }
  // Step 2: Seek to blockPointers[blockNum] and write buf to disk.
 
  disk.seekp((inodeIndex[index].blockPointers[blockNum]*blockSize), std::ios::beg);
  disk.write(buf, blockSize);

  return 0;
} // end write
