#include <stdio.h>
#include <stdlib.h>

int * encontrar(int n) {
    int *V = (int *)malloc((n + 1) * sizeof(int));
    V[0] = 1;
    for (int i = 1; i <= n; i++) {
        V[i] = 0;
        if (i - 1 >= 0) V[i] += V[i - 1];
        if (i - 3 >= 0) V[i] += V[i - 3];
        if (i - 4 >= 0) V[i] += V[i - 4];
    }
    return V;
}

void backtrack(int n, int V[], int combinacion[], int longitud) {
    if (n == 0) {
        for (int i = longitud - 1; i >= 0; i--) {
            printf("%d", combinacion[i]);
            if (i > 0) printf(" + ");
        }
        printf("\n");
        return;
    }
    if (n - 1 >= 0 && V[n - 1] > 0) {
        combinacion[longitud] = 1;
        backtrack(n - 1, V, combinacion, longitud + 1);
    }
    if (n - 3 >= 0 && V[n - 3] > 0) {
        combinacion[longitud] = 3;
        backtrack(n - 3, V, combinacion, longitud + 1);
    }
    if (n - 4 >= 0 && V[n - 4] > 0) {
        combinacion[longitud] = 4;
        backtrack(n - 4, V, combinacion, longitud + 1);
    }
}

int main() {
    int n;
    int combinacion[100];
    printf("Ingresa n: ");
    scanf("%d", &n);
    int *V = encontrar(n);
    printf("Combinaciones:\n");
    backtrack(n, V, combinacion, 0);
    printf("Total de combinaciones: %d\n", V[n]);
    free(V);
    return 0;
}