#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

// Does some bitwise operations and generates a 64bit hash
unsigned long bitHash(string value)
{
	unsigned long bitwise_hash = 0;
    int len = value.length();
    for(int i=0; i<len; i++)
    {
        bitwise_hash = bitwise_hash ^ ((bitwise_hash<<5) + (bitwise_hash>>2) + value[i]);
    }
    return bitwise_hash;
}

// tableSize is the size of array maintained by the hashtable
unsigned long divCompression(unsigned long hash, long tableSize)
{
	unsigned long result = hash %tableSize;
    return result; 
}

#endif
