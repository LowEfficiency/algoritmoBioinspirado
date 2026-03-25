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
        matriz[0][i].valor = ((double)rand() / RAND_MAX) * 2.0 - 1.0;; matriz[0][i].index = i;
        matriz[1][i].valor = ((double)rand() / RAND_MAX) * 2.0 - 1.0;;  matriz[1][i].index = i;


        (*resultado)[i].pais = malloc(2 * sizeof(pop));
    }
    
    return matriz;
}
void soma(result *r, pop **m, int *n){
    for (int i = 0; i < *n; i++){
        double x1 = m[0][i].valor;
        double x2 = m[1][i].valor;

        r[i].valor = (x1 * x1) + pow((x2 - 1.0), 2);
        r[i].index = i; 
        r[i].pais[0].valor = x1; r[i].pais[1].valor = x2;
    }
}
result verificaResultado(result *r, pop **m, int *n){
    double h;

    for (int i = 0; i < *n; i++){
        double x1 = m[0][i].valor;
        double x2 = m[1][i].valor;

       h = x2 - (x1 * x1);
        if(fabs(h) > 0.0001) { 
            r[i].valor += fabs(h) * 10000.0;
        }
    }
    result menor = r[0];
    for (int i = 1; i < *n; i++){ 
        if(r[i].valor < menor.valor)
            menor = r[i];
    }
    return menor;
       
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
int main(){
    int n = 100000;
    result *r;
    srand(time(NULL));

    pop **m = iniciaMatriz(&n, &r);


    soma(r,m, &n);
    result final = verificaResultado(r,m,&n);

    printf("resultado: valor -> %lf; pais: %lf, %lf; index: %d \n", final.valor, 
        final.pais[0].valor, final.pais[1].valor, final.index);
    liberaMemoria(m, r, &n);
}