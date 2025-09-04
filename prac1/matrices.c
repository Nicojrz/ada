#include <stdio.h>
#include <stdlib.h>

//juarezbarriosaxelnicolas

void crearMatriz(int ***A, int n);
void llenarMatriz(int ***A, int n);
void triangular(int *A, int n);

int main()
{
    return 0;
}

void crearMatriz(int ***A, int n)
{
    int i,j;
    *A = (int **)malloc(sizeof(int *)*n);
    for(i = 0; i < n; i++)
    {
        (*A)[i] = (int *)malloc(sizeof(int)*n);
    }
}

void llenarMatriz(int ***A, int n)
{
    int i,j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            (*A)[i][j] = 0;
        }
    }
}

void triangular(int *A, int ***B, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = i; j < n; j++)
        {
            if(i == j)
            {
                (*A)[i][j] = -1;
            }
            else
            {
                (*A)[i][j] = 
            }
        }
    }
}