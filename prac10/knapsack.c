#include <stdio.h>
#include <stdlib.h>

int maxi(int a, int b)
{
    return (a > b) ? a : b;
}

int **generarMatriz(int n, int m)
{
    int i, j;
    int **M = (int **)malloc(n * sizeof(int *));
    for(i = 0; i < n; i++)
    {	
        M[i] = (int *)malloc(m * sizeof(int));
        for (j = 0; j < m; j++)
            M[i][j] = 0;
    }	
    return M;
}

void liberarMatriz(int ***M, int n)
{
    int i;
    for(i = 0; i < n; i++)
        free((*M)[i]);
    free(*M);
}

int **knapsack(int n, int W, int *wi, int *vi)
{
    int i, j;
    int **V = generarMatriz(n+1, W+1);

    for(i = 1; i <= n; i++)
        for(j = 1; j <= W; j++)
            if(wi[i] <= j)
                V[i][j] = maxi(
                    V[i-1][j],
                    V[i-1][j-wi[i]] + vi[i]
                );
            else
                V[i][j] = V[i-1][j];

    return V;
}

void guardarMatriz(int **M, int n, int W, const char *filename)
{
    FILE *f = fopen(filename, "w");
    int i, j;

    for(i = 0; i <= n; i++)
    {
        for(j = 0; j <= W; j++)
        {
            printf("%3d ", M[i][j]);
            fprintf(f, "%d ", M[i][j]);
        }
        printf("\n");
        fprintf(f, "\n");
    }

    fclose(f);
}

void leerObjetos(const char *filename, int *n, int *W, int **wi, int **vi)
{
    FILE *f = fopen(filename, "r");
    int i;

    fscanf(f, "%d %d", n, W);

    *wi = (int *)malloc((*n + 1) * sizeof(int));
    *vi = (int *)malloc((*n + 1) * sizeof(int));

    for(i = 1; i <= *n; i++)
        fscanf(f, "%d %d", &(*wi)[i], &(*vi)[i]);

    fclose(f);
}

int main()
{
    int n, W;
    int *wi, *vi;
    char archivo[100];
    char archivoSalida[120];
    printf("Ingresa el nombre del archivo: ");
    scanf("%99s", archivo);
    leerObjetos(archivo, &n, &W, &wi, &vi);
    int **V = knapsack(n, W, wi, vi);
    printf("Matriz DP:\n");
    sprintf(archivoSalida, "matriz_%s", archivo);
    guardarMatriz(V, n, W, archivoSalida);
    liberarMatriz(&V, n + 1);
    free(wi);
    free(vi);
    return 0;
}
