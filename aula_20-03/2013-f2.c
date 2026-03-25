#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    double valor;
    int index;
} pop;

typedef struct {
    double valor;
    pop *pais;
    int index;
} result;

void imprimePop(pop p) {
    printf("[Index: %d | Valor: %.4f] ", p.index, p.valor);
}

pop **iniciaMatriz(int *n, result **resultado){
    pop **matriz = malloc(2 * sizeof(pop *));
    for (int i = 0; i < 2; i++)
        matriz[i] = malloc((*n) * sizeof(pop));

    *resultado = malloc((*n) * sizeof(result));


    for (int i = 0; i < *n; i++){
        matriz[0][i].valor = (double)rand() / (double)RAND_MAX; matriz[0][i].index = i;
        matriz[1][i].valor = (double)rand() / (double)RAND_MAX; matriz[1][i].index = i;


        (*resultado)[i].pais = malloc(2 * sizeof(pop));
    }
    
    return matriz;
}
void liberaMemoria(pop **m, result *r, int *n) {
    if (r != NULL) {
        for (int i = 0; i < *n; i++) {
            free(r[i].pais);
        }
        free(r);
    }

    if (m != NULL) {
        free(m[0]);
        free(m[1]);
        free(m);
    }
}
void soma(result *r, pop **m, int *n){
    for (int i = 0; i < *n; i++){
        double x1 = m[0][i].valor;
    
        r[i].valor =  pow(sin(5 * M_PI * x1), 6); r[i].pais[0].valor = x1;
        r[i].index = i;
    }
}
result verificaResultado(result *r, pop **m, int *n){
    result menor = r[0];
    for (int i = 1; i < *n; i++){ 
        if(r[i].valor < menor.valor)
            menor = r[i];
    }
    return menor;   
}
int main(){
    int n = 100000;
    result *r;
    srand(time(NULL));

    pop **m = iniciaMatriz(&n, &r);

    
    soma(r,m, &n);
    result final = verificaResultado(r,m,&n);   

    printf("resultado: valor -> %lf; pai: %lf; index: %d \n", final.valor, 
        final.pais[0].valor, final.index);
    liberaMemoria(m, r, &n);
}