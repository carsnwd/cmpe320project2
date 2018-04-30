
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convertIntToBinary(int numberToConvert);
int charBinaryToInt(char *binary);
// char* convertBinaryToTwosCompliment(char *binaryString);
 
int main(){
    int dec;
    char *bin;
    char *twosCompliment = malloc(1001);
 
    printf("Enter a decimal number: ");
    scanf("%d", &dec);
    printf("Your decimal is %d \n", dec);
    bin = convertIntToBinary(dec);
    int i = 0;
    printf("Binary of your decimal is signed twos comp is %s\n", bin);
    // twosCompliment = convertBinaryToTwosCompliment(bin);
    // printf("Twos Compliment is %s \n", twosCompliment);
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
    char *returnString = malloc(1001);
    returnString[0] = '0';
    return strcat(returnString, binaryString);
}

int charBinaryToInt(char *binary){

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

