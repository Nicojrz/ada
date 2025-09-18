#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 1
#define MAX 100
#define SIZE 5

//juarezbarriosaxelnicolas
void crearVector(int **A, int n);
void crearMatriz(int ***A, int n);
void llenarMatriz(int ***A, int n);
void randomVector(int **A, int n);
void imprimirMatriz(int **A, int n);
void imprimirVector(int *x, int n);
void triangular(int *x, int ***A, int n);

int main()
{
    int *vector;
    int **matriz;
    crearMatriz(&matriz, SIZE);
    llenarMatriz(&matriz, SIZE);
    imprimirMatriz(matriz, SIZE);
    printf("\n");
    crearVector(&vector, SIZE);
    randomVector(&vector, SIZE);
    imprimirVector(vector, SIZE);
    printf("\n");
    triangular(vector, &matriz, SIZE);
    imprimirMatriz(matriz, SIZE);
    return 0;
}

void crearMatriz(int ***A, int n)
{
    int i;
    *A = (int **)malloc(sizeof(int *)*n);
    for(i = 0; i < n; i ++)
    {
        (*A)[i] = (int *)malloc(sizeof(int)*n);
    }
}

void liberarMatriz(int ***A, int n)
{
    int i;
    for(i = 0; i < n; i ++)
    {
        free((*A)[i]);
    }
    free(*A);
    *A = NULL;
}

void crearVector(int **x, int n)
{
    *x = (int *)malloc(sizeof(int)*n);
}

void llenarMatriz(int ***A, int n)
{
    int i,j;
    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < n; j ++)
        {
            (*A)[i][j] = 0;
        }
    }
}

void randomVector(int **A, int n)
{
    int i,j, randlet;
    srand(time(NULL));
    for(i = 0; i < n; i ++)
    {
        randlet = (rand() % (MAX - MIN + 1)) + MIN;
        (*A)[i] = randlet;
    }
}

void imprimirMatriz(int **A, int n)
{
    int i,j;
    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < n; j ++)
        {
            printf("%d\t", A[i][j]);
            if((j+1)%n == 0)
                printf("\n");
        }
    }
}

void imprimirVector(int *x, int n)
{
    int i;
    for(i = 0; i < n; i ++)
        printf("%d\t", x[i]);
    printf("\n");
}

void triangular(int *x, int ***A, int n)
{
    int i, j;
    int suma;
    for(i = 0; i < n; i++)
    {
        suma = 0;
        for(j = i; j < n; j++)
        {
            suma += x[j];
            if(i != j)
                (*A)[i][j] = suma;
        }
    }
}