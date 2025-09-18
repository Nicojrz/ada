#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MIN -50
#define MAX 50

//juarezbarriosaxelnicolas
void generarCoeficientes(int **A, int n);
int evaluarPolinomio1(int *A, int a, int n);
int evaluarPolinomio2(int *A, int a, int n);

int main()
{
    int i, size, eval, *coef;
    srand(time(NULL));
    printf("Ingresa el numero de coeficientes:\n");
    scanf("%d", &size);
    generarCoeficientes(&coef, size);
    for(i = 0; i < size; i ++)
    {
        printf("[%d]", coef[i]);
    }
    printf("\n");
    printf("Ingresa el numero a evaluar en el polinomio:\n");
    scanf("%d", &eval);
    printf("Resultado algoritmo 1: %d\n", evaluarPolinomio1(coef, eval, size));
    printf("Resultado algoritmo 2: %d\n", evaluarPolinomio2(coef, eval, size));
    free(coef);
    return 0;
}

void generarCoeficientes(int **A, int n)
{
    int i, randlet;
    *A = (int *)malloc(sizeof(int)*n);
    for(i = 0; i < n; i ++)
    {
        randlet = (rand() % (MAX - MIN + 1)) + MIN;
        (*A)[i] = randlet;
    }
}

int evaluarPolinomio1(int *A, int a, int n)
{
    int i, resultado = 0;
    for(i = 0; i < n; i ++)
        resultado += (A[i]*(int)pow((double)a,(double)i));
    return resultado;
}

int evaluarPolinomio2(int *A, int a, int n)
{
    int i, suma = 0;
    for(i = (n-1); i >= 0; i --)
        suma = A[i] + a * suma;
    return suma;
}