#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* convertIntToBinary(int numberToConvert);
int convertBinaryToInt(char *binary);
int getPageNumber(int dec);
int getOffset(int dec);
void prepend(char* s, const char* t);
char **getVirtualAddressesValues();
char **getVirtualAddressTable();

char *virtualAddressTable[1000];
int pageTable[256];
int nextFrameNumberGiven;
int pageFault;
int tlb[16][2];
int tlbHits;
int tlbFifo;
const int ADDRESS_COUNT = 1000;

int main(){
    int dec;
    char *bin;
    char *virtualAddressValuesTable;
    nextFrameNumberGiven=0;
    pageFault = 0;
    tlbHits = 0;
    tlbFifo = 0;
    int i = 0;
    for(i = 0; i < 256; i++){
        pageTable[i] = -1;
    }
    
    virtualAddressValuesTable = getVirtualAddressesValues();
    getVirtualAddressTable();

    for(int i = 0; i < ADDRESS_COUNT; i++){
        int pageNumber = getPageNumber(atoi(virtualAddressTable[i]));
        int offset = getOffset(atoi(virtualAddressTable[i]));
        int frameNumber = locateFrame(pageNumber);
        int physicalAddress = calculatePhysicalAddress(frameNumber, offset);
        printf("Virtual Address = %s Physical Address = %d Value = %d\n", virtualAddressTable[i], physicalAddress,virtualAddressValuesTable[atoi(virtualAddressTable[i])]);
    }
    printf("Count of Addresses %d\n", ADDRESS_COUNT);
    printf("Faults = %d\n", pageFault);
    double rate1 = (double)pageFault/1000.00;
    printf("Fault rate = %f\n", rate1);
    printf("TLB Hits = %d\n", tlbHits);
    double rate2 = (double)tlbHits/1000.00;
    printf("TLB Rate = %f\n", rate2);
}

int calculatePhysicalAddress(int frameNumber, int offset){
    return (frameNumber*256) + offset;
}

int locateFrame(int pageNumber){
    int i = 0;
    for(i = 0; i<16; i++){
        if(tlb[i][0] == pageNumber){
            tlbHits++;
            return tlb[i][1];
        }
    }
    
    if(pageTable[pageNumber] != -1){
        if(tlbFifo == 16){
            tlbFifo = 0;
        }
        tlb[tlbFifo][0] = pageNumber; 
        tlb[tlbFifo][1] = pageTable[pageNumber];
        tlbFifo++; 
        return pageTable[pageNumber];
    }
    pageFault++;
    pageTable[pageNumber] = nextFrameNumberGiven;
    nextFrameNumberGiven++;
    if(tlbFifo == 16){
            tlbFifo = 0;
    }
    tlb[tlbFifo][0] = pageNumber; 
    tlb[tlbFifo][1] = pageTable[pageNumber]; 
    tlbFifo++;
    return pageTable[pageNumber];
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
    *returnString = NULL;
    int length = strlen(binaryString);
    while(length != 16){ //convert to 16 bit string
        //prepend(returnString, "0");
        returnString = strcat(returnString,"0");
        length++;
    }
    char* stuff = strcat(returnString, binaryString);
    return stuff;
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
    char* bin = convertIntToBinary(dec);
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
