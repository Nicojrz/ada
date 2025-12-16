#include <stdio.h>
#include <stdlib.h>

void liberarMatriz(int ***M, int n)
{
    int i;
    for(i = 0; i < n; i++)
        free((*M)[i]);
    free(*M);
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

int **leerMatriz(const char *filename, int n, int W)
{
    FILE *f = fopen(filename, "r");
    int i, j;

    int **M = generarMatriz(n+1, W+1);

    for(i = 0; i <= n; i++)
        for(j = 0; j <= W; j++)
            fscanf(f, "%d", &M[i][j]);

    fclose(f);
    return M;
}

void objetosSeleccionados(int **dp, int *wi, int n, int W)
{
    int i;
    int pesoRestante = W;

    printf("Objetos seleccionados:\n");

    for(i = n; i >= 1; i--)
    {
        if(dp[i][pesoRestante] != dp[i-1][pesoRestante])
        {
            printf("Objeto %d (peso=%d)\n", i, wi[i]);
            pesoRestante -= wi[i];
        }
    }
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
    char archivoObjetos[100];
    char archivoMatriz[100];
    printf("Ingresa el nombre del archivo de objetos: ");
    scanf("%99s", archivoObjetos);
    leerObjetos(archivoObjetos, &n, &W, &wi, &vi);
	printf("Ingresa el nombre del archivo de la matriz: ");
    scanf("%99s", archivoMatriz);
	int **dp = leerMatriz(archivoMatriz, n, W);
	objetosSeleccionados(dp, wi, n, W);
	liberarMatriz(&dp, n+1);
	return 0;
}
