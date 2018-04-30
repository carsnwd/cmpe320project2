
#include <stdio.h>
#include <stdlib.h>

int convert(int);
char* convertIntToBinary(int numberToConvert);
 
int main()
{
    int dec;
    char *bin;
    char *twosCompliment;
 
    printf("Enter a decimal number: ");
    scanf("%d", &dec);
    printf("Your decimal is %d \n", dec);
    bin = convertIntToBinary(dec);
    int i = 0;
    printf("Binary of your decimal is %s", bin);
    // *twosCompliment = convertBinarytoTwosCompliment(*bin);
    // printf("The binary equivalent of %d is %d.\n", dec, bin);
 
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
        printf("k = %d , i = %d , j = %d\n", k,i,j);
        binaryString[k] = binaryArray[j] + '0';
        printf("binaryArray[%d] %d\n",j,binaryArray[j]);
        printf("binaryString[%d] %d \n",k,binaryString[k]);
        k++;
    }

    printf("Inside convertfunc, your binary is %s\n", binaryString);
    return binaryString;
}

