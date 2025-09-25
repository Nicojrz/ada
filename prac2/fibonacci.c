#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double recfib(int n);
double itefib(int n);

int main(int argc, char *argv[])
{
	clock_t ini, end;
    double sec;
	int num, mode;
	ini = clock();
	switch (argc)
    {
		case 1:
			printf("Ingresa un numero...\n");
			scanf("%d", &num);
			printf("Ingresa el modo...\n");
			scanf("%d", &mode);
			if(mode == 0)
				printf("Resultado: %lf\n", recfib(num));
			else if(mode == 1)
				printf("Resultado: %lf\n", itefib(num));
			break;
		case 3:
			num = strtoull(argv[1], NULL, 10);
            mode = strtoull(argv[2], NULL, 10);
			printf("Numero: %d\tModo: %d\n", num, mode);
			if(mode == 0)
				printf("Resultado: %lf\n", recfib(num));
			else if(mode == 1)
				printf("Resultado: %lf\n", itefib(num));
			break;
		default:
			break;
	}
	end = clock();
	sec = ((double)(end - ini)) / CLOCKS_PER_SEC; 
    printf("Tiempo de ejecucion: %f segundos\n", sec);
	return 0;
}

double recfib(int n)
{
	if(n == 0) return 0;
	if(n == 1) return 1;
	if(n >= 2) return recfib(n-1) + recfib(n-2);
}

double itefib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    double *x = malloc(sizeof(double) * (n+1));
    if (!x) return -1;
    x[0] = 0; x[1] = 1;
    for (int i = 2; i <= n; i++)
        x[i] = x[i-2] + x[i-1];
    double res = x[n];  
    free(x);             
    return res;
}