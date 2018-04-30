
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//NOTE!!!! RUN WITH gcc main.c -lm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char* convertIntToBinary(int numberToConvert);
int convertBinaryToInt(char *binary);
int getPageNumber(int dec);
int getOffset(int dec);
// char* convertBinaryToTwosCompliment(char *binaryString);
 
int main(){
    int dec;
    char *bin;
    char *twosCompliment = malloc(1001);
 
    printf("Enter a decimal number: ");
    scanf("%d", &dec);
    printf("Your decimal is %d \n", dec);
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
    returnString[0] = '0';
    return strcat(returnString, binaryString);
}

int convertBinaryToInt(char *binary){
    int length = strlen(binary) - 2;
    int count = 0;
    int sum = 0;
    for(int i = length; i>=0; i--){
        if(binary[i] == '1'){
            sum = sum + pow(2,(length - count));
        }
        count++;
    }
    return sum;
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
    char offsetBinary[8];
    memcpy(offsetBinary, &bin[9], 7);
    offsetBinary[7] = '\0';
    int offsetDecimal = convertBinaryToInt(offsetBinary);
    return offsetDecimal;
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

