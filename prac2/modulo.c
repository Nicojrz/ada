#include <stdio.h>
#include <stdlib.h>

int explin(int a, int n);
int explog(int a, int n);

int main(int argc, char *argv[])
{
	int a, m, n, mode, res;
	switch (argc)
    {
        case 1:
			printf("Ingresa el numero a:\n");
            scanf("%d", &a);
            printf("Ingresa el numero m:\n");
            scanf("%d", &m);
			printf("Ingresa el numero n:\n");
            scanf("%d", &n);
			printf("Ingresa el modo:\n");
            scanf("%d", &mode);
            res = ammodn(x, y, mode);
            
            printf("Resultado %d^%d mod %d = %d\n", a, m, n, res);
			break;
        case 5:
			a = strtoull(argv[1], NULL, 10);
            m = strtoull(argv[2], NULL, 10);
            n = strtoull(argv[3], NULL, 10);
            mode = strtoull(argv[4], NULL, 10);
            res = ammodn(x, y, mode);
			
			printf("Resultado %d^%d mod %d = %d\n", a, m, n, res);
			break;
		default:
			printf("Mas de 4 numeros ingresados.\n");
			break;
	}
	
	return 0;
}

int ammodn(int a, int m, int n, int MODE)
{
	int pot, res;
	//variable MODE para alternar entre algoritmos de potencias.
	switch(MODE)
	{
		//potencia lineal
		case 0:
			pot = explin(a, m);
			res = pot % n;
			break;
		//potencia logaritmica
		case 1:
			pot = explog(a, m);
			res = pot % n;
			break;
		default:
			printf("MODE invalido.\n");
			return -1;
			break;
	}
}

int explin(int a, int n)
{
	int i, res = 1;
	for(i = 0; i < n; i++)
		res *= a;
	return res;
}

int explog(int a, int n)
{ 	 
	if (n == 0) return 1;
		
	if (n%2 == 1)
		return (a * explog(a, n-1));
	else
	{
		int temp = explog(a, n/2);
		return temp * temp;
	}
}