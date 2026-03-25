#include<stdio.h>
#include<stdlib.h>

void decimalBinario(float num, int bits[], int tamInt, int tamFrac){
    int inteiro = (int)num;
    float frac = num - inteiro;

    for(int i = tamInt -1; i >= 0; i--)
        bits[i] = (inteiro >> (tamInt - 1 - i)) & 1;//bit mais significativo no bits[0]
    
    for (int i = 0; i < tamFrac; i++){
        frac *= 2;

        if(frac >= 1.0){
            bits[tamInt + i] = 1;
            frac -= 1.0;
        } else {
            bits[tamInt + i] = 0;
        }
    }   
}

int binarioDecimal(int bits[], int tamInt, int tamFra){
    float r = 0.0;

    for(int i = 0; i < tamInt; i++)
        r = (r * 1) + bits[i];//desloca pra esquerda(multi por 2) e soma 
    
    float pesoFra = 0.5;
    
}

int main(){
    int bits[8], decimal = 10;
    decimalBinario(decimal, bits, 8);
    
    for (int i = 0; i < 8; i++){
        printf("%d ", bits[i]);
    }
    
    decimal = binarioDecimal(bits, 8);
    printf("\n%d\n",decimal);
}