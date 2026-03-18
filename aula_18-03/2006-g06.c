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


pop **iniciaMatriz(int *n, result **resultado){
    pop **matriz = malloc(2 * sizeof(pop *));
    for (int i = 0; i < 2; i++)
        matriz[i] = malloc((*n) * sizeof(pop));

    *resultado = malloc((*n) * sizeof(result));


    for (int i = 0; i < *n; i++){
        matriz[0][i].valor = 13.0 + ((double)rand() / RAND_MAX) * 87.0; matriz[0][i].index = i;
        matriz[1][i].valor = ((double)rand() / RAND_MAX) * 100;  matriz[1][i].index = i;


        (*resultado)[i].pais = malloc(2 * sizeof(pop));
    }
    
    return matriz;
}

result verificaResultado(result *r, pop **m, int *n){
    double g1,g2;
    
    for (int i = 0; i < *n; i++){
        double x1 = m[0][i].valor;
        double x2 = m[1][i].valor;

        g1 = - pow((x1 - 5), 2) - pow((x2 - 5), 5) + 100;
        g2 = pow((x1 - 6), 2) + pow((x2 - 5), 5) - 82.81;

        double penalizacao = (g1 + g2) * 100;
        r[i].valor += penalizacao;
    }
    
    result menor = r[0];
    for (int i = 1; i < *n; i++){ 
        if(r[i].valor < menor.valor)
            menor = r[i];
    }
    return menor;
}

void soma(result *r, pop **m, int *n){
    for(int i = 0; i < *n; i++){
        double x1 = m[0][i].valor;
        double x2 = m[1][i].valor;
        
        r[i].valor = pow((x1 - 10), 3) + pow((x2 - 20), 3);
        r[i].index = i;
        r[i].pais[0] = m[0][i]; r[i].pais[1] = m[1][i]; 
    }
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
    int n = 1000;
    result *r;
    int count = 0;
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        pop **m = iniciaMatriz(&n, &r);
        soma(r,m, &n);
        result final = verificaResultado(r,m,&n);
        printf("resultado: valor -> %lf; pais: %lf, %lf; index: %d \n", final.valor, final.pais[0], final.pais[1], final.index);
        liberaMemoria(m, r, &n);
    }
    
}