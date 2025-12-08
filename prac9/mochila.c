#include <stdio.h>

typedef struct {
    int id;
    double peso;
    double valor;
    double razon;
} Objeto;

// mergesort

void merge(Objeto arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    Objeto L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // ordenar v/p
    while (i < n1 && j < n2)
	{
        if (L[i].razon >= R[j].razon)
            arr[k++] = L[i++];
		else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(Objeto arr[], int l, int r)
{
    if (l < r)
	{
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// mochila

double mochilaFraccionaria(Objeto objs[], int n, double W)
{
    mergeSort(objs, 0, n - 1); 

    double capacidad = W;
    double valorTotal = 0.0;

    printf("\nObjetos tomados:\n");

    for (int i = 0; i < n; i++)
	{
        if (capacidad <= 0)
            break;

        if (objs[i].peso <= capacidad)
		{
            printf(" - Objeto %d: 100%% (valor %.2lf)\n",
                    objs[i].id, objs[i].valor);

            capacidad -= objs[i].peso;
            valorTotal += objs[i].valor;

        }
		else
		{
            double fraccion = capacidad / objs[i].peso;

            printf(" - Objeto %d: %.2lf%% (valor %.2lf)\n",
                    objs[i].id,
                    fraccion * 100,
                    objs[i].valor * fraccion);

            valorTotal += objs[i].valor * fraccion;
            capacidad = 0;
        }
    }

    return valorTotal;
}

// main

int main()
{
    int n;
    double W;

    printf("Peso maximo de la mochila W: ");
    scanf("%lf", &W);

    printf("Numero de objetos: ");
    scanf("%d", &n);

    Objeto objs[n];

    for (int i = 0; i < n; i++) {
        printf("Objeto %d - peso: ", i + 1);
        scanf("%lf", &objs[i].peso);

        printf("Objeto %d - valor: ", i + 1);
        scanf("%lf", &objs[i].valor);

        objs[i].razon = objs[i].valor / objs[i].peso;
        objs[i].id = i + 1;
    }

    double total = mochilaFraccionaria(objs, n, W);

    printf("\nValor total obtenido: %.2lf\n", total);

    return 0;
}
