#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int s_matrix0[4][4] = { {1,0,3,2},
						{3,2,1,0},
						{0,2,1,3},
						{3,1,3,2} };


int s_matrix1[4][4] = { {0,1,2,3},
						{2,0,1,3},
						{3,0,1,0},
						{2,1,0,3} };


int s0=0, s1=0;
int row=0, col=0;
int s0_binary[2], s1_binary[2];
int result[2];


int to_digit(int a, int b)
{
    int output;
    if(a==1 && b==1)
        output = 3;


    if(a==0 && b==1)
        output = 1;


    if(a==1 && b==0)
        output = 2;


    if(a==0 && b==0)
        output = 0;


    return output;
}


void to_binary(int num)
{
    int x;


    if(num == 3)
    {
        for(x=0; x<2; x++)
            result[x] = 1;
    }
    else if(num == 1)
    {
        result[0] = 0;
        result[1] = 1;
    }
    else if(num == 2)
    {
        result[0] = 1;
        result[1] = 0;
    }
    else if(num == 0)
    {
        for(x=0; x<2; x++)
            result[x] = 0;
    }
}


// Function to convert a character to binary representation
void char_to_binary(char c, int binary_arrays[][8], size_t index) {
    // Loop through each bit in the character (assuming 8-bit ASCII)
    for (int i = 7; i >= 0; i--) {
        // Store each bit in the corresponding binary array
        binary_arrays[index][i] = (c >> i) & 1;
    }
}


// Function to convert a string to binary representation
void string_to_binary(const char *str, int binary_arrays[][8], size_t max_length) {
    // Loop through each character in the string
    for (size_t i = 0; i < strlen(str) && i < max_length; i++) {
        // Convert each character to binary and store it in the corresponding binary array
        char_to_binary(str[i], binary_arrays, i);
    }
}


char binaryToDecimal(int n) 
{ 
    int num = n; 
    int dec_value = 0; 
  
    // Initializing base value to 1, i.e 2^0 
    int base = 1; 
  
    int temp = num; 
    // Extracting the last digit of the binary number 
    while (temp) { 
        int last_digit = temp % 10; 
        // Removing the last digit from the binary number 
        temp = temp / 10; 
  
        // Multiplying the last digit with the base value 
        // and adding it to the decimal value 
        dec_value += last_digit * base; 
  
        // Updating the base value by multiplying it by 2 
        base = base * 2; 
    } 
  
    // Returning the decimal value 

    char c = dec_value;
    return c; 
} 


void EncryptPasssword(char input_pass[8],int encrpted_password[8])
{
    int i,j,index;


    char str[9]; // String to convert to binary (change as needed)
    for(int i=0;i<9;i++){
        if(input_pass[i]!='\0'){
            str[i]=input_pass[i];
        }else{
           str[i]=input_pass[i];
           break; 
        }
    }
    printf("000001%s\n",str);
    int binary_arrays[8][8]; // Arrays to store binary representation of each character


    // Convert string to binary representation and store it in binary_arrays
    string_to_binary(str, binary_arrays, sizeof(binary_arrays) / sizeof(binary_arrays[0]));


    int k1[8], k2[8];
    int afterp10[11], ls1[10], ls2[10], afterip[8], afterep[8], afterp4[4];
    int aftersboxesone[4], aftersboxestwo[4];
    int leftafterip[4], rightafterip[4];
    int leftafterep[4], rightafterep[4];
    int leftafterone[4], rightafterone[4];
    int afteripinverse[8];
    int afterone[8], aftertwo[8];


    int p10[10] = {3,5,2,7,4,10,1,9,8,6};
    int p8[8] = {6,3,7,4,8,5,10,9};


    int ip[8] = {2,6,3,1,4,8,5,7};
    int ep[8] = {4,1,2,3,2,3,4,1};
    int p4[4] = {2,4,3,1};
    int ipinverse[8] = {4,1,3,5,7,2,8,6};


    int key[11] = {1,0,1,0,0,0,0,0,1,0};
    int plain[8];


    //S-DES Key Generation and Encryption


    //\n----------KEY GENERATION----------


    for(i=0; i<=9; i++)
    {
        index = p10[i];
        afterp10[i] = key[index - 1];
    }
    afterp10[i] = '\0';


    //After p10


    for(i=0; i<5; i++)
    {
        if(i == 4)
            ls1[i]=afterp10[0];
        else
            ls1[i]=afterp10[i+1];
    }


    for(i=5; i<10; i++)
    {
        if(i == 9)
            ls1[i]=afterp10[5];
        else
            ls1[i]=afterp10[i+1];
    }


    //After LS-1


    index=0;
    for(i=0; i<=9; i++)
    {
        index = p8[i];
        k1[i] = ls1[index - 1];
    }


    //After p8 Key-1 is generated


    for(i=0; i<3; i++)
    {
        ls2[i]=ls1[i+2];
    }
    ls2[3]=ls1[0];
    ls2[4]=ls1[1];


    for(i=5; i<8; i++)
    {
        ls2[i]=ls1[i+2];
    }
    ls2[8]=ls1[5];
    ls2[9]=ls1[6];


    //After LS-2


    index=0;
    for(i=0; i<=9; i++)
    {
        index = p8[i];
        k2[i] = ls2[index - 1];
    }


    //After p8 Key-2 is generated


    //----------S-DES ENCRYPTION---------
for (size_t k = 0; k < strlen(str); k++) {
    for (int n = 0; n < 8; n++) { 
        plain[n] = binary_arrays[k][n]; 
    }
    for(i=0; i<8; i++)
    {
        index = ip[i];
        afterip[i] = plain[index - 1];
    }
    afterip[i] = '\0';


    //After ip


    for(j=0; j<4; j++)
    {
        leftafterip[j] = afterip[j];
    }
    for(j=0; j<4; j++)
    {
        rightafterip[j] = afterip[j+4];
    }
    for(i=0; i<4; i++)
    {
        index = ep[i];
        afterep[i] = rightafterip[index - 1];
    }


    for(i=4; i<8; i++)
    {
        index = ep[i];
        afterep[i] = rightafterip[index - 1];
    }
    afterep[i] = '\0';


    //After ep


    for(i=0; i<8; i++)
    {
        k1[i] = k1[i] ^ afterep[i];
    }
    //After XOR operation with 1st Key


    row = to_digit(k1[0],k1[3]);
    col = to_digit(k1[1],k1[2]);
    s0 = s_matrix0[row][col];


    to_binary(s0);
    for(j=0; j<2; j++)
        s0_binary[j] = result[j];


    row = to_digit(k1[4],k1[7]);
    col = to_digit(k1[5],k1[6]);


    s1 = s_matrix1[row][col];


    to_binary(s1);
    for(j=0; j<2; j++)
    {
        s1_binary[j] = result[j];
    }
    for(j=0; j<2; j++)
    {
        aftersboxesone[j] = s0_binary[j];
    }
    for(i=0,j=2; i<2,j<4; i++,j++)
    {
        aftersboxesone[j] = s1_binary[i];
    }
    //After first S-Boxes


    for(i=0; i<4; i++)
    {
        index = p4[i];
        afterp4[i] = aftersboxesone[index - 1];
    }
    afterp4[i] = '\0';


    //After P4


    for(i=0; i<4; i++)
    {
        afterp4[i] = afterp4[i] ^ leftafterip[i];
    }
    //After XOR operation with left nibble of after ip


    for(i=0; i<4; i++)
    {
        afterone[i] = rightafterip[i];
    }
    for(i=0,j=4; i<4,j<8; i++,j++)
    {
        afterone[j] = afterp4[i];
    }
    afterone[j] = '\0';


    //After first part


    for(j=0; j<4; j++)
    {
        leftafterone[j] = afterone[j];
    }
    for(j=0; j<4; j++)
    {
        rightafterone[j] = afterone[j+4];
    }
    for(i=0; i<4; i++)
    {
        index = ep[i];
        afterep[i] = rightafterone[index - 1];
    }


    for(i=4; i<8; i++)
    {
        index = ep[i];
        afterep[i] = rightafterone[index - 1];
    }
    afterep[i] = '\0';


    //After second ep


    for(i=0; i<8; i++)
    {
        k2[i] = k2[i] ^ afterep[i];
    }
    //After XOR operation with 2nd Key


    row = to_digit(k2[0],k2[3]);
    col = to_digit(k2[1],k2[2]);


    s0 = s_matrix0[row][col];
    to_binary(s0);
    for(j=0; j<2; j++)
    {
        s0_binary[j] = result[j];
    }
    row = to_digit(k2[4],k2[7]);
    col = to_digit(k2[5],k2[6]);


    s1 = s_matrix1[row][col];
    to_binary(s1);
    for(j=0; j<2; j++)
    {
        s1_binary[j] = result[j];
    }
    for(j=0; j<2; j++)
    {
        aftersboxestwo[j] = s0_binary[j];
    }
    for(i=0,j=2; i<2,j<4; i++,j++)
    {
        aftersboxestwo[j] = s1_binary[i];
    }
    //After second S-Boxes


    for(i=0; i<4; i++)
    {
        index = p4[i];
        afterp4[i] = aftersboxestwo[index - 1];
    }
    afterp4[i] = '\0';


    //After P4


    for(i=0; i<4; i++)
    {
        afterp4[i] = afterp4[i] ^ leftafterone[i];
    }
    //After XOR operation with left nibble of after first part


    for(i=0; i<4; i++)
    {
        aftertwo[i] = afterp4[i];
    }
    for(i=0,j=4; i<4,j<8; i++,j++)
    {
        aftertwo[j] = rightafterone[i];
    }
    aftertwo[j] = '\0';


    //After second part


    for(i=0; i<8; i++)
    {
        index = ipinverse[i];
        afteripinverse[i] = aftertwo[index - 1];
    }
    afteripinverse[j] = '\0';


    printf("--->8-bit Ciphertext will be= ");
    for(i=0; i<=j; i++)
    {
        printf("%d",afteripinverse[i]);
        encrpted_password[i]=afteripinverse[i];
    }
printf("\n");
}

printf("done\n");

}
