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
float binarioDecimal(int bits[], int tamInt, int tamFra){
    float r = 0.0;

    for(int i = 0; i < tamInt; i++)
        r = (r * 2) + bits[i];//desloca pra esquerda(multi por 2) e soma 
    
    float pesoFra = 0.5;
    for(int i = tamInt; i< (tamInt + tamFra); i++){
        if(bits[i] == 1)
            r += pesoFra;
        pesoFra /= 2;
    }
    return r;
}
float** alocaMatrizFloat(int n){
    float **m = (float**)malloc(n * sizeof(float *));
    for (size_t i = 0; i < n; i++)
        m[i] = (float *)malloc(2 * sizeof(float));
    return m;
}
int*** alocaMatrizBinaria(int n, int tamTotal){
    int ***m = (int***)malloc(n * sizeof(int **));
    for (size_t i = 0; i < n; i++){
        m[i] = (int**)malloc(2 * sizeof(int*));
        m[i][0] = (int*)malloc(tamTotal * sizeof(int));
        m[i][1] = (int*)malloc(tamTotal * sizeof(int));
    }
    return m;
}
float* alocaVetorResultado(int n){
    float *r = (float*)malloc(n * sizeof(float));
    return r;
}
void liberarMatrizFloat(float **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}
void liberarMatrizBinaria(int ***m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i][0]);
        free(m[i][1]);
        free(m[i]);
    }
    free(m);
}
float geraFloat8_16(){
unsigned int r24 = ((rand() << 12) ^ rand()) & 0xFFFFFF;
return (float)r24 / 65536.0f;
}
void iniciaMatrizes(float **mfloat, int***mBin, int n, int tInt,int tFrac){
    for (size_t i = 0; i < n; i++){
        float x = geraFloat8_16();
        mfloat[i][0] = x;
        decimalBinario(x, mBin[i][0], tInt,tFrac);

        float y = geraFloat8_16();
        mfloat[i][1] = y;
        decimalBinario(y, mBin[i][1], tInt,tFrac);
    }
}

int main(){
   
}