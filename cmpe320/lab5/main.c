
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashmap.c"
#define PHYSICAL_MEMORY_SIZE 25;

//NOTE!!!! RUN WITH gcc main.c -lm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char* convertIntToBinary(int numberToConvert);
int convertBinaryToInt(char *binary);
int getPageNumber(int dec);
int getOffset(int dec);
void prepend(char* s, const char* t);
char **getVirtualAddressesValues();
char **getVirtualAddressTable();
char *virtualAddressTable[1000];


int main(){
    int dec;
    char *bin;
    char *virtualAddressValuesTable;
    // char *virtualAddressTable;
 
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

    
    virtualAddressValuesTable = getVirtualAddressesValues();
    //printf("virtualAddressValuesTable[30198] = %d", virtualAddressValuesTable[30198]);
    getVirtualAddressTable();

    // printf("Getting offset and pagenumber for %d\n", atoi(virtualAddressTable[0]));
    // int dummy = getPageNumber(atoi(virtualAddressTable[0]));
    // int pageNumber = getPageNumber(atoi(virtualAddressTable[0]));
    // int offset = getOffset(atoi(virtualAddressTable[0]));
    // printf("paggenumber = %d   offset = %d\n", pageNumber, offset);

    // printf("virtualAddressValuesTable[%d]\n", atoi(virtualAddressTable[2]));
    // printf("virtualAddressValuesTable[atoi(virtualAddressTable[2])] = %d\n", virtualAddressValuesTable[atoi(virtualAddressTable[2])]);
    // printf("virtualAddressTable[2] = %d\n", atoi(virtualAddressTable[2]));
    // printf("pageNumber = %d\n", pageNumber);
    // printf("offset = %d", offset);
    // insert(virtualAddressValuesTable[atoi(virtualAddressTable[2])], atoi(virtualAddressTable[2]), pageNumber, offset);
    // int physicalAddress = hashFunction(virtualAddressTable[0], pageNumber, offset);
    // printf("Virtual Address = %d Value = %d  Physical Address = %d\n\n", atoi(virtualAddressTable[0]), virtualAddressValuesTable[atoi(virtualAddressTable[0])], physicalAddress);
    
    for(int i = 0; i <= 999; i++){
        int dummy = getPageNumber(atoi(virtualAddressTable[i]));
        int pageNumber = getPageNumber(atoi(virtualAddressTable[i]));
        int offset = getOffset(atoi(virtualAddressTable[i]));
        // printf("pageNumber = %d  offset = %d\n", pageNumber, offset);
        int physicalAddress = hashFunction(virtualAddressTable[0], pageNumber, offset);
        printf("Value = %d  Physical Address = %d Virtual Address = %s \n", virtualAddressValuesTable[atoi(virtualAddressTable[i])], physicalAddress, virtualAddressTable[i]);
        // if(i ==3){
        //      break;
        // }
    }

    // printf("virtualAddressTable[0] = %s", virtualAddressTable[0]);
    // int testIndex = atoi(virtualAddressTable[2]);
    // printf("virtualAddressValuesTable[virtualAddressTable[2]] = %d", virtualAddressValuesTable[testIndex]);
    // return 0;
    //physicalAddress = page * frame + offset

    // insert(10,0);
    // int val = getHashValue(0);
    // printf("Value = %d", val);
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
    // printf("bin = %s\n", bin);
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
    // printf("bin %s\n", bin);
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

/**
 * Gets all the virtual address values
 */
char **getVirtualAddressesValues(){
    char *virtualAddressValuesTable;
    unsigned long fileLen;
    FILE *ptr;
    ptr = fopen("BACKING_STORE.bin","rb");
    fseek(ptr, 0, SEEK_END);
    fileLen = ftell(ptr);
    fseek(ptr, 0, SEEK_SET);

    virtualAddressValuesTable = (char *)malloc(fileLen+1);
    fread(virtualAddressValuesTable, fileLen, 1, ptr);
    fclose(ptr);
    return virtualAddressValuesTable;
}

char **getVirtualAddressTable(){
    // char *virtualAddressTable;
    unsigned long fileLen;
    FILE *ptr;
    ptr = fopen("addresses.txt", "r");
    fseek(ptr, 0, SEEK_END);
    fileLen = ftell(ptr);
    fseek(ptr, 0, SEEK_SET);

    // virtualAddressTable = (char *)malloc(fileLen+1);
    // fread(virtualAddressTable, fileLen, 1, ptr);

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), ptr)) {
        virtualAddressTable[i] = strdup(line);
        if(i ==0){
            // printf("virtualAddressTable[%d] = %s",i,virtualAddressTable[i]);
        }
        i++;
    }

    fclose(ptr);
    return virtualAddressTable;
}

