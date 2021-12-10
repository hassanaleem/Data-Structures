#ifndef CHAINING_CPP
#define CHAINING_CPP

#include "Chaining.h"
#include "HashFunction.cpp"


// Constructor
HashC::HashC(int size)
{
	tableSize = size;
    hashTable.reset(new LinkedList<string>[tableSize], default_delete<LinkedList<string>[]>());
}


// Destructor
HashC::~HashC()
{
	
}


// Given a String, return its hash
unsigned long HashC::hash(string input)
{
    return bitHash(input);
}


// Takes a hash of 'word' and inserts it into hashTable accordingly
void HashC::insertWord(string word)
{
    int index = divCompression(hash(word), tableSize);
    hashTable.get()[index].insertAtHead(word);
}


// Locates 'word' in the hash table and returns a pointer to it
shared_ptr<ListItem<string>> HashC::lookupWord(string word)
{
	int index = divCompression(hash(word), tableSize);
    return hashTable.get()[index].searchFor(word);

}


// Deletes 'word' from the hash table
void HashC::deleteWord(string word)
{
	int index = divCompression(hash(word), tableSize);
    hashTable.get()[index].deleteElement(word);
    
}


#endif