#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int mini(int a, int b)
{
    return (a < b) ? a : b;
}

int cambio(int n, int k, int *D)
{
    int i, j;
    int *Dp = (int *)malloc(sizeof(int) * (n + 1));

    for (i = 0; i <= n; i++) {
        Dp[i] = INT_MAX;
    }
    Dp[0] = 0;

    for (i = 1; i <= n; i++) {
        for (j = 0; j < k; j++) {
            if (D[j] <= i) {
                Dp[i] = mini(Dp[i], Dp[i - D[j]] + 1);
            }
        }
    }

    int resultado = (Dp[n] == INT_MAX) ? -1 : Dp[n];
    free(Dp);
    return resultado;
}

int main()
{
    int i;
    int den[3] = {1, 7, 10};
    for (i = 0; i < 3; i++) {
        printf("[%d] ", den[i]);
    }
    int cmin = cambio(15, 3, den);
    if (cmin != -1)
        printf("\nCambio mínimo: %d\n", cmin);
    else
        printf("\nNo es posible hacer el cambio\n");
    return 0;
}
