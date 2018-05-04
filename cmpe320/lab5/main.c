
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
// char* convertBinaryToTwosCompliment(char *binaryString);
 
int main(){
    int dec;
    char *bin;
    //char *twosCompliment = malloc(1001);
 
    printf("Enter a decimal number: ");
    fflush(stdout);
    scanf("%d", &dec);
    printf("Your decimal is %d \n", dec);
    fflush(stdout);
    bin = convertIntToBinary(dec);
    printf("Your binary is %s\n", bin);
    int pageNumber = getPageNumber(dec);
    printf("The page number is: %d\n", pageNumber);
    int offset = getOffset(dec);
    printf("The offset number is: %d\n", offset);
    return 0;
}

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

int convertBinaryToInt(char *binary){
    return (int) strtol(binary, NULL, 2);
    // int length = strlen(binary) - 1;
    // int count = 0;
    // int sum = 0;
    // for(int i = length; i>=0; i--){
    //     if(binary[i] == '1'){
    //         sum = sum + pow(2,(length - count));
    //     }
    //     count++;
    // }
    // return sum;
}

int getPageNumber(int dec){
    char *bin = convertIntToBinary(dec);
    char pageNumberBinary[9];
    memcpy(pageNumberBinary, &bin[0], 8);
    pageNumberBinary[8] = '\0';
    int pageNumberDecimal = convertBinaryToInt(pageNumberBinary);
    return pageNumberDecimal;
}

int getOffset(int dec){
    char *bin = convertIntToBinary(dec);
    char offsetBinary[9];
    memcpy(offsetBinary, &bin[8], 8);
    offsetBinary[8] = '\0';
    int offsetDecimal = convertBinaryToInt(offsetBinary);
    return offsetDecimal;
}

void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i){
        s[i] = t[i];
    }
}

// char *convertBinaryToTwosCompliment(char *binaryString){
//     int i;
//     int n = strlen(binaryString);
//     for (i = n ; i >= 0 ; i--){
//         if (binaryString[i] == '1'){
//             break;
//         }
//     }
//     if(i==0){
//         return '1' + binaryString;
//     }
//     for (int k = i-1 ; k >= 0; k--){
//         //Just flip the values
//         if (binaryString[k] == '1'){
//             binaryString[k] = '0';
//         }
//         else{
//             binaryString[k] = '1';
//         }
//     }
//     return binaryString;
// }

