#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PHYSICAL_MEMORY_SIZE 256

struct HashMapItem{
    int index;
    int value;
};

struct HashMapItem *pageTable[PHYSICAL_MEMORY_SIZE];

/**
 * Hash Function
 * Was unsure what hash function to use, so found one
 * that was well researched and tested...
 * https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key 
 **/
unsigned int hashFunction(int index){
    index = ((index >> 16) ^ index) * 0x45d9f3b;
    index = ((index >> 16) ^ index) * 0x45d9f3b;
    int hashedIndex = (index >> 16) ^ index;
    return hashedIndex;
}

/**
 * Insert a value into the hash map given value and index.
 **/
void insert(int value, int index){
    struct HashMapItem *item = (struct HashMapItem*)malloc(sizeof(struct HashMapItem));
    item->value=value;
    item->index=index;
    
    int hashIndex = hashFunction(index);
    pageTable[hashIndex] = item;
}

/**
 * Get item at index in hashmap 
 **/
int getHashValue(int index){
    int hashValue = pageTable[hashFunction(index)]->value;
    return hashValue;
}

