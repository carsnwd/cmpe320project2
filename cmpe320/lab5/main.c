
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//NOTE!!!! RUN WITH gcc main.c -lm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char* convertIntToBinary(int numberToConvert);
int convertBinaryToInt(char *binary);
int getPageNumber(int dec);
int getOffset(int dec);
void prepend(char* s, const char* t);
char **createPageTable();
 
int main(){
    // int dec;
    // char *bin;
    char *pageTable;
 
    // printf("Enter a decimal number: ");
    // fflush(stdout);
    // scanf("%d", &dec);
    // printf("Your decimal is %d \n", dec);
    // fflush(stdout);
    // bin = convertIntToBinary(dec);
    // printf("Your binary is %s\n", bin);
    // int pageNumber = getPageNumber(dec);
    // printf("The page number is: %d\n", pageNumber);
    // int offset = getOffset(dec);
    // printf("The offset number is: %d\n", offset);

    pageTable = createPageTable();
    printf("758 -> %d\n", pageTable[758]);
    printf("Physical Address -> %p\n", &pageTable[758]);
    return 0;
}

/**
 * Converts an int to binary string. 
 **/
char *convertIntToBinary(int numberToConvert){
    char *binaryString = malloc(1001);
    int binaryArray[1000];
    int i = 0;
    while(numberToConvert > 0){
        binaryArray[i] = numberToConvert % 2;
        numberToConvert = numberToConvert / 2;
        i++;
    }

    int k = 0;
    for (int j = i - 1; j >= 0; j--){
        binaryString[k] = binaryArray[j] + '0';
        k++;
    }

    char *returnString = malloc(1001);
    int length = strlen(binaryString);
    while(length != 16){ //convert to 16 bit string
            prepend(returnString, "0");
            length++;
    }
    return strcat(returnString, binaryString);
}

/**
 * Converts a binary string to an int. 
 **/
int convertBinaryToInt(char *binary){
    return (int) strtol(binary, NULL, 2);
}

/**
 * Given the int, it will get he page number.
 **/
int getPageNumber(int dec){
    char *bin = convertIntToBinary(dec);
    char pageNumberBinary[9];
    memcpy(pageNumberBinary, &bin[0], 8);
    pageNumberBinary[8] = '\0';
    int pageNumberDecimal = convertBinaryToInt(pageNumberBinary);
    return pageNumberDecimal;
}

/**
 * Given the int, it will get he offset.
 **/
int getOffset(int dec){
    char *bin = convertIntToBinary(dec);
    char offsetBinary[9];
    memcpy(offsetBinary, &bin[8], 8);
    offsetBinary[8] = '\0';
    int offsetDecimal = convertBinaryToInt(offsetBinary);
    return offsetDecimal;
}

/**
 * Prepends a char infront of a string.
 ***/
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i){
        s[i] = t[i];
    }
}

char **createPageTable(){
    char *pageTable;
    unsigned long fileLen;
    FILE *ptr;
    ptr = fopen("BACKING_STORE.bin","rb");
    fseek(ptr, 0, SEEK_END);
    fileLen = ftell(ptr);
    fseek(ptr, 0, SEEK_SET);

    pageTable = (char *)malloc(fileLen+1);
    fread(pageTable, fileLen, 1, ptr);
    fclose(ptr);
    return pageTable;
}