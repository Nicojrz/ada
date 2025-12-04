#include <stdio.h>
#include <stdlib.h>

// DISJOINT-SET

typedef struct {
    int padre;
    int rango;
} Conjunto;

void crearConjunto(Conjunto conjuntos[], int n)
{
    for (int i = 0; i < n; i++)
	{
        conjuntos[i].padre = i;
        conjuntos[i].rango = 0;
    }
}

int encontrar(Conjunto conjuntos[], int x)
{
    if (conjuntos[x].padre != x)
        conjuntos[x].padre = encontrar(conjuntos, conjuntos[x].padre);
    return conjuntos[x].padre;
}

void unir(Conjunto conjuntos[], int x, int y)
{
    int rx = encontrar(conjuntos, x);
    int ry = encontrar(conjuntos, y);

    if (rx != ry)
	{
        if (conjuntos[rx].rango < conjuntos[ry].rango)
            conjuntos[rx].padre = ry;
        else if (conjuntos[rx].rango > conjuntos[ry].rango)
            conjuntos[ry].padre = rx;
        else
		{
            conjuntos[ry].padre = rx;
            conjuntos[rx].rango++;
        }
    }
}

// NODOS

typedef struct {
    int origen;
    int destino;
    int peso;
} Arista;

// Implementación de merge-sort para aristas.
void merge(Arista arr[], int izq, int mid, int der)
{
    int tam1 = mid - izq + 1;
    int tam2 = der - mid;

    Arista *izquierda = malloc(tam1 * sizeof(Arista));
    Arista *derecha = malloc(tam2 * sizeof(Arista));

    for (int i = 0; i < tam1; i++) izquierda[i] = arr[izq + i];
    for (int i = 0; i < tam2; i++) derecha[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = izq;

    while (i < tam1 && j < tam2)
	{
        if (izquierda[i].peso <= derecha[j].peso)
		{
            arr[k++] = izquierda[i++];
        }
		else
		{
            arr[k++] = derecha[j++];
        }
    }

    while (i < tam1) arr[k++] = izquierda[i++];
    while (j < tam2) arr[k++] = derecha[j++];

    free(izquierda);
    free(derecha);
}

void mergesort(Arista arr[], int izq, int der)
{
    if (izq < der)
	{
        int mid = (izq + der) / 2;
        mergesort(arr, izq, mid);
        mergesort(arr, mid + 1, der);
        merge(arr, izq, mid, der);
    }
}

// Grafo

Arista* leerGrafo(char nombre_archivo[], int *n, int *m)
{
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo)
	{
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }

    fscanf(archivo, "%d %d", n, m);

    Arista *aristas = malloc((*m) * sizeof(Arista));

    for (int i = 0; i < *m; i++)
	{
        fscanf(archivo, "%d %d %d", 
               &aristas[i].origen, &aristas[i].destino, &aristas[i].peso);
    }

    fclose(archivo);
    return aristas;
}

// KRUSKAL

void kruskal(Arista aristas[], int n, int m)
{
    printf("KRUSKAL ---\n");

    // Ordenamos aristas
    mergesort(aristas, 0, m - 1);

    printf("Aristas ordenadas por peso (merge-sort)---\n");
    for (int i = 0; i < m; i++)
        printf("(%d, %d) peso = %d\n", aristas[i].origen, aristas[i].destino, aristas[i].peso);

    Conjunto *conjuntos = malloc(n * sizeof(Conjunto));
    crearConjunto(conjuntos, n);

    Arista *mst = malloc((n - 1) * sizeof(Arista));
    int total = 0, contador = 0;

    printf("Paso a paso ---\n");

    for (int i = 0; i < m; i++)
	{
        int u = aristas[i].origen;
        int v = aristas[i].destino;

        int ru = encontrar(conjuntos, u);
        int rv = encontrar(conjuntos, v);

        printf("Considerando arista (%d,%d) peso=%d\n", u, v, aristas[i].peso);

        if (ru != rv)
		{
            printf("Se agrega al arbol (no forma ciclo)\n");
            mst[contador++] = aristas[i];
            total += aristas[i].peso;
            unir(conjuntos, ru, rv);
        }
		else
		{
            printf("Se descarta (forma ciclo)\n");
        }
    }

    printf("Arbol de recubrimiento minimo ---\n");
    for (int i = 0; i < contador; i++)
        printf("(%d, %d) peso=%d\n", mst[i].origen, mst[i].destino, mst[i].peso);

    printf("Costo total del arbol: %d\n", total);

    free(conjuntos);
    free(mst);
}

// MAIN

int main()
{
    char archivo[100];
	
	printf("Ingresa el nombre del archivo:\n");
    scanf("%s", archivo);

    int n, m;
    Arista *aristas = leerGrafo(archivo, &n, &m);

    printf("Numero de nodos: %d\n", n);
    printf("Numero de aristas: %d\n", m);

    printf("Aristas leidas ---\n");
    for (int i = 0; i < m; i++)
        printf("(%d, %d) peso=%d\n", aristas[i].origen, aristas[i].destino, aristas[i].peso);

    kruskal(aristas, n, m);

    free(aristas);
    return 0;
}