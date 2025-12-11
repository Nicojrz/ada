#include <stdio.h>
#include <stdlib.h>

int maxi(int a, int b)
{
	return (a > b) ? a : b;
}

int **genMatrix(int n, int m)
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

void freeMatrix(int ***M, int n)
{
	int i;
	for(i = 0; i < n; i++)
		free(*M[i]);
	free(*M);
}

int knapsack(int n, int W, int *wi, int *vi)
{
	int i, j;
	int **V = genMatrix(n+1, W+1);
	
	for(i = 1; i <= n; i++)
		for(j = 1; j <= W; j++)
			if(wi[i] <= W)
				V[i][j] = maxi(V[i-1][j], V[i-1][j-wi[i]] + vi[i]);
			else
				V[i][j] = V[i-1][j];

	int max = V[n][W];
	freeMatrix(&V, n);

	return max;
}

int main()
{
	return 0;
}
