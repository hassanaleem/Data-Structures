#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "LinearProbing.h"
#include "HashFunction.cpp"
#include <memory>

// Constructor
HashL::HashL(int size)
{
    tableSize = size;
    //hashTable.clear();
    hashTable.resize(tableSize);
    count = 0;
}


// Destructor
HashL::~HashL()
{
    
}

// Computes the key corresponding to the value.
unsigned long HashL::hash(string value)
{
	return bitHash(value);
}

// Function to resize the hash table
void HashL::resizeTable()
{
    tableSize = tableSize*50;
	vector<shared_ptr<tableItem>> temp = hashTable;
    hashTable.resize(tableSize);

    int size = temp.size();
    int index = 0;
    for(int i=0;i<size; i++)
    {
        shared_ptr<tableItem> ptr = temp.back();
        temp.pop_back(); 
        if(ptr)
        {
            index = divCompression(hash(ptr->value), tableSize);
            while(hashTable[index])
            {
                index++;
                index = index % tableSize;
            }

            hashTable[index] = ptr;
        }
       
        
        
    }
}

// Takes the hash of 'value' and insert it into the hash table
void HashL::insertWord(string value)
{
    //double check= count*1.0/tableSize ;
    if(count*1.0/tableSize > 0.5)
    {
        resizeTable();
    }

    int index = divCompression(hash(value), tableSize);
    while(hashTable[index])
    {
        index++;
        index = index % tableSize; 
    }

    shared_ptr<tableItem> temp(new tableItem(0,value));
    hashTable[index] = temp;
    count++;

    
    
}

// Deletes 'value' from the hash table.
void HashL::deleteWord(string value)
{
    unsigned long check = 99;
	int index = divCompression(hash(value), tableSize);
    while(hashTable[index])
    {
        if(hashTable[index]->value == value && hashTable[index]->key != check)
        {
            hashTable[index]->key = check;
            return;
        }
        index++;
        index = index % tableSize;
    }
    return;
   
}

// Locates value in the hash table and returns a pointer to it
shared_ptr<tableItem> HashL::lookupWord(string value)
{
    unsigned long check = 99;
    int index = divCompression(hash(value), tableSize);
    int temp_index = index;
    while(hashTable[index])
    {
        if(hashTable[index]->key == check && hashTable[index]->value == value)
        {
            return NULL;
        }
        if(hashTable[index]->value == value)
        {
            break;
        }
        index++;
        index = index % tableSize;
       
    }
    return hashTable[index];

}

#endif
