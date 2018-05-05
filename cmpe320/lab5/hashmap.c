#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "main.c"
#define PHYSICAL_MEMORY_SIZE 256
int frame = 0;

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
unsigned int hashFunction(char *indexString, int pageNumber, int offset){
    // index = ((index >> 16) ^ index) * 0x45d9f3b;
    // index = ((index >> 16) ^ index) * 0x45d9f3b;
    // int hashedIndex = (index >> 16) ^ index;
    // return hashedIndex;
    int index = atoi(indexString);
    int hashedIndex = 256 * frame + offset;
    // printf("\n%d = %d * %d + %d\n", hashedIndex, pageNumber, frame, offset);
    frame++;
    return hashedIndex;
}

/**
 * Insert a value into the hash map given value and index.
 **/
void insert(int value, int index, int pageNumber, int offset){
    struct HashMapItem *item = (struct HashMapItem*)malloc(sizeof(struct HashMapItem));
    item->value=value;
    item->index=index;
    
    int hashIndex = hashFunction(index, pageNumber, offset);
    if(pageTable[hashIndex] == NULL){
        pageTable[hashIndex] = item;
    }else{

    }
}

/**
 * Get item at index in hashmap 
 **/
int getHashValue(int index, int pageNumber, int offset){
    int hashValue = pageTable[hashFunction(index, pageNumber, offset)]->value;
    return hashValue;
}