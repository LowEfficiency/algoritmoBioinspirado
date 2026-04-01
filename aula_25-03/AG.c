#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

typedef struct {
    float x;
    float y;
    float fitness;
} MelhorIndividuo;

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

float* alocaVetorFit(int n){
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

float* calculaFit(float **mf, int n){
    float *fit = alocaVetorFit(n);
    for (size_t i = 0; i < n; i++){
        float x = mf[i][0];
        float y = mf[i][1];

        fit[i] = (x * x) + (y * y);
    }
    return fit;
}

int* selecao(int npop, float* fit){
    int* vpais = (int*)malloc(npop * sizeof(int));
    float pv = 0.9f;

    for (size_t i = 0; i < npop; i++){
        int p1 = rand() % npop;
        int p2 = rand() % npop;

        while(p1 == p2)
            p2 = rand() % npop;
        
        float r = (float)rand() / (float)RAND_MAX;
        int vencedor;

        if(fit[p1] < fit[p2])
            vencedor = (r < pv) ? p1 : p2;
        else
            vencedor = (r < pv) ? p2 : p1;
        
        vpais[i] = vencedor;
    }
    return vpais;
}

int*** novaPop(int ***mb, int *vp, int n, int tamtotal){
    int ***npop = alocaMatrizBinaria(n, tamtotal);
    for (size_t i = 0; i < n; i+=2){
        int idxPai1 = vp[i];
        int idxPai2 = vp[i+1];

        int pCorte = (rand() % (tamtotal - 1)) + 1;

        for (int var = 0; var < 2; var++){
            for (int b = 0; b < tamtotal; b++){
                if (b < pCorte){
                    npop[i][var][b] = mb[idxPai1][var][b];
                    npop[i+1][var][b] = mb[idxPai2][var][b];
                }else{
                    npop[i][var][b] = mb[idxPai2][var][b];
                    npop[i+1][var][b] = mb[idxPai1][var][b];
                }
            }   
        }
    }
    return npop;
}

MelhorIndividuo obterMelhor(float **mf, float *fit, int n) {
    MelhorIndividuo campeao;
    int melhorIdx = 0;

    for (int i = 1; i < n; i++) {
        if (fit[i] < fit[melhorIdx]) {
            melhorIdx = i;
        }
    }
    campeao.x = mf[melhorIdx][0];
    campeao.y = mf[melhorIdx][1];
    campeao.fitness = fit[melhorIdx];

    return campeao;
}

void mutacao(int ***mb, int n, int tamTotal, float taxaMutacao) {
    for (int i = 0; i < n; i++) {
        for (int var = 0; var < 2; var++) {
            for (int b = 0; b < tamTotal; b++) {
                float r = (float)rand() / (float)RAND_MAX;
                if (r < taxaMutacao) {
                    mb[i][var][b] = !mb[i][var][b]; 
                }
            }
        }
    }
}

int main(){
   srand(time(NULL));
   int n = 100, tint = 8, tfra = 16, nG = 30;
   int*** mb = alocaMatrizBinaria(n, tint + tfra);
   float** mf = alocaMatrizFloat(n);
   iniciaMatrizes(mf, mb, n, tint, tfra);

    //arquivo vai ser convertido para csv
    FILE *ptr;
    ptr = fopen("dados.csv","w");
    if(ptr == NULL){
        printf("Nao foi possivel formar o arquivo");
        return 1;
    }

    fprintf(ptr,"Geracao,Melhor_X,Melhor_Y,Fitness\n");
   for (int g = 0; g < nG; g++){//geracoes
        float *fit = calculaFit(mf, n);
        MelhorIndividuo rg = obterMelhor(mf, fit, n);
        printf("geracao %d | Melhor X: %.6f | Melhor Y: %.6f Fitness: %.6f\n", g + 1, rg.x, rg.y, rg.fitness);
        
        fprintf(ptr,"%d,%.6f,%.6f,%.6f\n",g+1,rg.x,rg.y,rg.fitness);

        int *vp = selecao(n, fit);
        int ***nmb = novaPop(mb, vp, n, 24);
        
        mutacao(nmb, n, tint + tfra, 0.01);

        liberarMatrizBinaria(mb, n);
        mb = nmb;   
        for (size_t i = 0; i < n; i++){
            mf[i][0] = binarioDecimal(mb[i][0], tint, tfra);
            mf[i][1] = binarioDecimal(mb[i][1], tint, tfra);
        }
        free(vp);
        free(fit);
   }
   
   fclose(ptr);

   float* fit = calculaFit(mf, n);
   MelhorIndividuo r = obterMelhor(mf, fit, n);
   printf("Melhor X final: %.6f\n", r.x);
   printf("Melhor Y final: %.6f\n", r.y);
   printf("Fitness final: %.6f (Objetivo: 0.0000)\n", r.fitness);
   liberarMatrizBinaria(mb, n);
   liberarMatrizFloat(mf, n);
   return 0;
}
